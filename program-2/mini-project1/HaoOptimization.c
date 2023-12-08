#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// for lex
#define MAXLEN 256

// Token types
typedef enum
{
    UNKNOWN,
    END,
    ENDFILE,
    INT,
    ID,
    ADDSUB,
    MULDIV,
    ASSIGN,
    LPAREN,
    RPAREN,
    INCDEC,        // new
    ADDSUB_ASSIGN, // new
    AND,           // new
    XOR,           // new
    OR             // new
} TokenSet;

TokenSet getToken(void);
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];

// Test if a token matches the current token
int match(TokenSet token);
// Get the next token
void advance(void);
// Get the lexeme of the current token
char *getLexeme(void);

// for parser
#define TBLSIZE 64

// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 0

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum)                                                       \
    {                                                                         \
        if (PRINTERR)                                                         \
            fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
        err(errorNum);                                                        \
    }

// Error types
typedef enum
{
    UNDEFINED,
    MISPAREN,
    NOTNUMID,
    NOTFOUND,
    RUNOUT,
    NOTLVAL,
    DIVZERO,
    SYNTAXERR
} ErrorType;

// Structure of the symbol table
typedef struct
{
    int isConst;
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node
{
    TokenSet data;
    int isConst;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

int sbcount = 0;
Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
void initTable(void);
// Get the value of a variable
int getval(char *str);
// Set the value of a variable
int setval(char *str, int val);
// Make a new node according to token type and lexeme
BTNode *makeNode(TokenSet tok, const char *lexe);
// Free the syntax tree
void freeTree(BTNode *root);

void statement(void);
BTNode *assign_expr();
BTNode *or_expr();
BTNode *or_expr_tail(BTNode *left);
BTNode *xor_expr();
BTNode *xor_expr_tail(BTNode *left);
BTNode *and_expr();
BTNode *and_expr_tail(BTNode *left);
BTNode *addsub_expr();
BTNode *addsub_expr_tail(BTNode *left);
BTNode *muldiv_expr();
BTNode *muldiv_expr_tail(BTNode *left);
BTNode *unary_expr();
BTNode *factor(void);

// Print error message and exit the program
void err(ErrorType errorNum);

// for codeGen
// Evaluate the syntax tree
int evaluateTree(BTNode *root);
// check if exist ID
int checkID(BTNode *root);
// get top reg
int topREG();
// push reg
int pushREG();
// pop REG
void popREG();
// Get address of varible
int getaddr(const char *str);
// regStack_index
int reg_idx = -1;
int isConstant(BTNode *root);
void assmbly_print(BTNode *root, int reg);
/*============================================================================================
lex implementation
============================================================================================*/

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t')
        ;
    if (isdigit(c))
    {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN)
        {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    }
    else if (c == '+' || c == '-') // change
    {
        lexeme[0] = c;
        c = fgetc(stdin);
        if ((c == '+' && lexeme[0] == '+') || (c == '-' && lexeme[0] == '-')) // important
        {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        }
        else if (c == '=')
        {
            lexeme[1] = c;
            lexeme[2] = '\0';
            return ADDSUB_ASSIGN;
        }
        else
        {
            ungetc(c, stdin);
            lexeme[1] = '\0';
            return ADDSUB;
        }
    }
    else if (c == '*' || c == '/')
    {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    }
    else if (c == '\n')
    {
        lexeme[0] = '\0';
        return END;
    }
    else if (c == '=')
    {
        strcpy(lexeme, "=");
        return ASSIGN;
    }
    else if (c == '(')
    {
        strcpy(lexeme, "(");
        return LPAREN;
    }
    else if (c == ')')
    {
        strcpy(lexeme, ")");
        return RPAREN;
    }
    else if (c == '&') // new
    {
        strcpy(lexeme, "&");
        return AND;
    }
    else if (c == '^') // new
    {
        strcpy(lexeme, "^");
        return XOR;
    }
    else if (c == '|') // new
    {
        strcpy(lexeme, "|");
        return OR;
    }
    else if (isalpha(c) || c == '_') // change
    {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isalpha(c) || isdigit(c) || c == '_') && i < MAXLEN)
        {
            lexeme[i++] = c;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    }
    else if (c == EOF)
    {
        return ENDFILE;
    }
    else
    {
        return UNKNOWN;
    }
}

void advance(void)
{
    curToken = getToken();
}

int match(TokenSet token)
{
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void)
{
    return lexeme;
}

/*============================================================================================
parser implementation
============================================================================================*/

void initTable(void)
{
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getval(char *str)
{
    int i = 0;
    for (i = 0; i < sbcount; i++)
    {
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;
    }

    if (sbcount >= TBLSIZE)
        err(RUNOUT);
    err(NOTFOUND);
    return 0;
}

int setval(char *str, int val)
{
    int i = 0;
    for (i = 0; i < sbcount; i++)
    {
        if (strcmp(str, table[i].name) == 0)
        {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        err(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe)
{
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// statement := ENDFILE | END | assign_expr END
void statement(void)
{
    BTNode *retp = NULL;
    if (match(ENDFILE))
    {
        for (int i = 0; i < 3; ++i)
            printf("MOV r%d [%d]\n", i, i * 4);
        printf("EXIT 0");
        exit(0);
    }
    else if (match(END))
    {
        advance();
    }
    else
    {
        retp = assign_expr();
        if (match(END))
        {
            if (!isConstant(retp))
                assmbly_print(retp, 0);
            freeTree(retp);
            advance();
        }
        else
        {
            err(SYNTAXERR);
        }
    }
}

// assign_expr := ID ASSIGN assign_expr | ID ADDSUB_ASSIGN assign_expr | or_expr
BTNode *assign_expr()
{
    BTNode *rept = NULL, *left = NULL;
    left = or_expr();
    if (match(ASSIGN))
    {
        if (left->data == ID)
        {
            rept = makeNode(ASSIGN, getLexeme());
            advance();
            rept->left = left;
            rept->right = assign_expr();
        }
        else
            err(SYNTAXERR);
    }
    else if (match(ADDSUB_ASSIGN))
    {
        if (left->data == ID)
        {
            rept = makeNode(ADDSUB_ASSIGN, getLexeme());
            advance();
            rept->left = left;
            rept->right = assign_expr();
        }
        else
            err(SYNTAXERR);
    }
    else
        rept = left;
    return rept;
}

// or_expr := xor_expr or_expr_tail
BTNode *or_expr()
{
    BTNode *node = xor_expr();
    return or_expr_tail(node);
}

// op_expr_tail := OR xor_expr op_expr_tail | NiL
BTNode *or_expr_tail(BTNode *left)
{
    BTNode *node = NULL;
    if (match(OR))
    {
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr();
        return or_expr_tail(node);
    }
    else
        return left;
}

// xor_expr := and_expr xor_exor_tail
BTNode *xor_expr()
{
    BTNode *node = and_expr();
    return xor_expr_tail(node);
}

// xor_expr_tail := XOR and_expr xor_expr_tail | NiL
BTNode *xor_expr_tail(BTNode *left)
{
    BTNode *node = NULL;
    if (match(XOR))
    {
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        return xor_expr_tail(node);
    }
    else
        return left;
}

// and_expr := addsub_expr and_expr_tail
BTNode *and_expr()
{
    BTNode *node = addsub_expr();
    return and_expr_tail(node);
}

// and_expr_tail := AND addsub_expr and_expr_tail | NiL
BTNode *and_expr_tail(BTNode *left)
{
    BTNode *node = NULL;
    if (match(AND))
    {
        node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr();
        return and_expr_tail(node);
    }
    else
        return left;
}

// addsub_expr := muldiv_expr addsub_expr_tail
BTNode *addsub_expr()
{
    BTNode *node = muldiv_expr();
    return addsub_expr_tail(node);
}

// addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | NiL
BTNode *addsub_expr_tail(BTNode *left)
{
    BTNode *node = NULL;
    if (match(ADDSUB))
    {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr();
        return addsub_expr_tail(node);
    }
    else
        return left;
}

// muldiv_expr := unary_expr muldiv_expr_tail | NiL
BTNode *muldiv_expr()
{
    BTNode *node = unary_expr();
    return muldiv_expr_tail(node);
}

// mildiv_expr_tail := MULDIV unary_expr muldiv_expr_tail | NiL
BTNode *muldiv_expr_tail(BTNode *left)
{
    BTNode *node = NULL;
    if (match(MULDIV))
    {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = unary_expr();
        return muldiv_expr_tail(node);
    }
    else
        return left;
}

// unary_expr := ADDSUB unary_expr | factor
BTNode *unary_expr()
{
    BTNode *rept = NULL, *right = NULL;
    if (match(ADDSUB))
    {
        rept = makeNode(ADDSUB, getLexeme());
        advance();
        rept->right = unary_expr();
        rept->left = makeNode(INT, "0");
    }
    else
    {
        rept = factor();
    }
    return rept;
}

// factor := INT | ID | INCDEC ID | LP assign_expr RP
BTNode *factor(void)
{
    BTNode *retp = NULL, *right = NULL;
    if (match(INT))
    {
        retp = makeNode(INT, getLexeme());
        advance();
    }
    else if (match(ID))
    {
        retp = makeNode(ID, getLexeme());
        advance();
    }
    else if (match(INCDEC))
    {
        retp = makeNode(INCDEC, getLexeme());
        advance();
        if (match(ID))
        {
            right = makeNode(ID, getLexeme());
            advance();
            retp->right = right;
        }
        else
        {
            error(SYNTAXERR);
        }
    }
    else if (match(LPAREN))
    {
        advance();
        retp = assign_expr();
        if (match(RPAREN))
            advance();
        else
            err(MISPAREN);
    }
    else
    {
        err(NOTNUMID);
    }
    return retp;
}

void err(ErrorType errorNum)
{
    printf("EXIT 1");
    if (PRINTERR)
    {
        fprintf(stderr, "error: ");
        switch (errorNum)
        {
        case MISPAREN:
            fprintf(stderr, "mismatched parenthesis\n");
            break;
        case NOTNUMID:
            fprintf(stderr, "number or identifier expected\n");
            break;
        case NOTFOUND:
            fprintf(stderr, "variable not defined\n");
            break;
        case RUNOUT:
            fprintf(stderr, "out of memory\n");
            break;
        case NOTLVAL:
            fprintf(stderr, "lvalue required as an operand\n");
            break;
        case DIVZERO:
            fprintf(stderr, "divide by constant zero\n");
            break;
        case SYNTAXERR:
            fprintf(stderr, "syntax error\n");
            break;
        default:
            fprintf(stderr, "undefined error\n");
            break;
        }
    }
    exit(0);
}

/*============================================================================================
codeGen implementation
============================================================================================*/

int reg[8] = {0, 1, 2, 3, 4, 5, 6, 7};

int isConstant(BTNode *root)
{
    int lv, rv = 0;
    if (root != NULL)
    {
        switch (root->data)
        {
        case ID:
            break;
        case INT:
            root->isConst = 1;
            root->val = atoi(root->lexeme);
            break;
        case ASSIGN:
            lv = isConstant(root->left);
            root->isConst = lv;
            if (root->isConst)
            {
                root->val = root->right->val;
                Symbol *it = &table[getaddr(root->left->lexeme)];
                it->isConst = 1;
                it->val = root->val;
            }
            break;
        case ADDSUB_ASSIGN:
            lv = isConstant(root->left);
            rv = isConstant(root->right);

            if (lv && rv)
            {
                root->isConst = 1;
                root->val = root->left->val + root->right->val;

                Symbol *it = &table[getaddr(root->left->lexeme)];
                it->isConst = 1;
                it->val = root->val;
            }
            break;
        case INCDEC:
            lv = isConstant(root->left);
            if (lv == 1)
            {
                root->isConst = 1;
                root->val = root->right->val + 1;

                Symbol *it = &table[getaddr(root->left->lexeme)];
                it->isConst = 1;
                it->val = root->val;
            }
            break;
        case ADDSUB:
        case MULDIV:
        case AND:
        case XOR:
        case OR:
            lv = isConstant(root->left);
            rv = isConstant(root->right);
            root->isConst = lv;
            if (lv && rv)
            {
                int lval = root->left->val, rval = root->right->val;
                if (!strcmp(root->lexeme, "+"))
                {
                    root->val = lval + rval;
                }
                if (!strcmp(root->lexeme, "-"))
                {
                    root->val = lval - rval;
                }
                if (!strcmp(root->lexeme, "*"))
                {
                    root->val = lval * rval;
                }
                if (!strcmp(root->lexeme, "/"))
                {
                    if (evaluateTree(root->right) == 0)
                    {
                        if (checkID(root->right))
                        {
                            root->val = lval / rval;
                        }
                        else
                        {
                            root->isConst = 0;
                        }
                    }
                    else
                    {
                        root->val = lval / rval;
                    }
                }
                if (!strcmp(root->lexeme, "&"))
                {
                    root->val = lval & rval;
                }
                if (!strcmp(root->lexeme, "|"))
                {
                    root->val = lval | rval;
                }
                if (!strcmp(root->lexeme, "^"))
                {
                    root->val = lval ^ rval;
                }
            }
            break;
        default:
            break;
        }
    }
    return root->isConst;
}

void assmbly_print(BTNode *root, int reg)
{
    int retval = 0, lv = 0, rv = 0;
    int REGID = -1, tmpREG = -1, addr;
    if (root != NULL)
    {
        switch (root->data)
        {
        case ID:
            addr = getaddr(root->lexeme);
            printf("MOV r%d [%d]\n", reg, addr);
            break;
        case INT:
            retval = atoi(root->lexeme);
            printf("MOV r%d %d\n", reg, retval);
            break;
        case ASSIGN:
            assmbly_print(root->right, reg);
            printf("MOV [%d] r%d\n", addr, reg);
            break;
        case ADDSUB_ASSIGN:
            assmbly_print(root->right, reg + 1);
            printf("MOV r%d [%d]\n", reg, addr);
            if (root->lexeme[0] == '-')
                printf("SUB r%d r%d\n", reg, reg + 1);
            else if (root->lexeme[0] == '+')
                printf("ADD r%d r%d\n", reg, reg + 1);

            printf("MOV [%d] r%d\n", addr, reg);
            break;
        case INCDEC:
            addr = getaddr(root->right->lexeme);
            printf("MOV r%d [%d]\n", reg, addr);
            printf("MOV r%d %d\n", reg + 1, 1);
            if (root->lexeme[0] == '-')
                printf("SUB r%d r%d\n", reg, reg + 1);
            else if (root->lexeme[0] == '+')
                printf("ADD r%d r%d\n", reg, reg + 1);
            printf("MOV [%d] r%d\n", addr, reg);
            break;
        case ADDSUB:
        case MULDIV:
        case AND:
        case XOR:
        case OR:
            assmbly_print(root->left, reg);
            assmbly_print(root->right, reg + 1);
            if (strcmp(root->lexeme, "+") == 0)
                printf("ADD r%d r%d\n", reg, reg + 1);
            else if (strcmp(root->lexeme, "-") == 0)
                printf("SUB r%d r%d\n", reg, reg + 1);
            else if (strcmp(root->lexeme, "*") == 0)
                printf("MUL r%d r%d\n", reg, reg + 1);
            else if (strcmp(root->lexeme, "/") == 0)
            {
                rv = evaluateTree(root->right);
                if (rv == 0)
                {
                    if (checkID(root->right))
                        printf("DIV r%d r%d\n", reg, reg + 1);
                    else
                        error(DIVZERO);
                }
                else
                    printf("DIV r%d r%d\n", reg, reg + 1);
            }
            else if (strcmp(root->lexeme, "|") == 0)
                printf("OR r%d r%d\n", reg, reg + 1);
            else if (strcmp(root->lexeme, "&") == 0)
                printf("AND r%d r%d\n", reg, reg + 1);
            else if (strcmp(root->lexeme, "^") == 0)
                printf("XOR r%d r%d\n", reg, reg + 1);
            break;
        }
    }
}

int topREG()
{
    return reg[reg_idx];
}

int pushREG()
{
    if (reg_idx >= 8)
    {
        err(RUNOUT);
        return -1;
    }
    else
        return reg[++reg_idx];
}

void popREG()
{
    if (reg_idx - 1 >= -1)
        reg_idx--;
    else
        err(RUNOUT);
}

int getaddr(const char *str)
{
    for (int i = 0; i < sbcount; i++)
    {
        if (strcmp(str, table[i].name) == 0)
        {
            return i * 4;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);
    return 0;
}

int checkID(BTNode *root)
{
    if (root)
    {
        if (root->data == ID)
            return 1;
        return checkID(root->left) || checkID(root->right);
    }
    return 0;
}

int evaluateTree(BTNode *root)
{
    int retval = 0, lv = 0, rv = 0;
    int REGID = -1, tmpREG = -1, addr;
    if (root != NULL)
    {
        switch (root->data)
        {
        case ID:
            retval = getval(root->lexeme);
            break;
        case INT:
            retval = atoi(root->lexeme);
            break;
        case ASSIGN:
            rv = evaluateTree(root->right);
            retval = setval(root->left->lexeme, rv);
            break;
        case ADDSUB_ASSIGN:
            lv = getval(root->left->lexeme);
            rv = evaluateTree(root->right);
            if (root->lexeme[0] == '-')
            {
                retval = setval(root->left->lexeme, lv - rv);
            }
            else if (root->lexeme[0] == '+')
            {
                retval = setval(root->left->lexeme, lv + rv);
            }
            break;
        case INCDEC:
            rv = getval(root->right->lexeme);
            if (root->lexeme[0] == '-')
            {
                retval = setval(root->right->lexeme, rv - 1);
            }
            else if (root->lexeme[0] == '+')
            {
                retval = setval(root->right->lexeme, rv + 1);
            }
            break;
        case ADDSUB:
        case MULDIV:
        case AND:
        case XOR:
        case OR:
            lv = evaluateTree(root->left);
            rv = evaluateTree(root->right);

            if (strcmp(root->lexeme, "+") == 0)
            {
                retval = lv + rv;
            }
            else if (strcmp(root->lexeme, "-") == 0)
            {
                retval = lv - rv;
            }
            else if (strcmp(root->lexeme, "*") == 0)
            {
                retval = lv * rv;
            }
            else if (strcmp(root->lexeme, "/") == 0)
            {
                retval = lv / rv;
            }
            else if (strcmp(root->lexeme, "|") == 0)
            {
                retval = lv | rv;
            }
            else if (strcmp(root->lexeme, "&") == 0)
            {
                retval = lv & rv;
            }
            else if (strcmp(root->lexeme, "^") == 0)
            {
                retval = lv ^ rv;
            }
            break;
        default:
            retval = 0;
        }
    }
    return retval;
}

/*============================================================================================
main
============================================================================================*/

int main()
{
    // freopen("1-test.txt", "r", stdin);
    // freopen("2-input.txt", "w", stdout);
    initTable();
    while (1)
        statement();
    return 0;
}
