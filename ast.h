#ifndef AST_H_
#define AST_H_

#include "token.h"

typedef enum { e_value_exp, e_binary_op, e_unary_op, e_fnc_call } enum_expr_tag;

typedef struct expr_tag {
    enum_expr_tag tag;
    union {
        token*                                  value;
        struct { token*            oper;
                 struct expr_tag*  left;
                 struct expr_tag*  right; }     binary;
        struct { token*            oper;
                 struct expr_tag*  operand; }   unary;
        struct { struct expr_tag*  fnc;
                 struct expr_list* params; }     fnc_call;
        } content;
} expr;

typedef struct expr_list {
    expr* elem;
    struct expr_list* next;
} expr_list;

typedef enum { e_block_stmt, e_while_stmt, e_if_stmt,
               e_expr_stmt, e_declare_stmt } enum_stmt_tag;

typedef struct stmt_tag {
    enum_stmt_tag tag;
    union {
        expr*                                _expr;
        struct block*                        _block;
        struct { expr*            cond;
                 struct stmt_tag* stmt; }    _while;
        struct { expr*            cond;
                 struct stmt_tag* stmt;
                 struct stmt_tag* alter; }   _if;
        struct { token*           type;
                 token*           var; }     _declare;
    } content;
} stmt;

typedef struct block {
    stmt* elem;
    struct block* next;
} block;

expr* new_value_expr(token* value);
expr* new_binary_op_expr(token* operator);
expr* new_unary_op_expr(token* operator);
expr* new_fnc_call_expr();
expr_list* new_expr_list(expr* elem);

stmt* new_expr_stmt(expr* elem);
stmt* new_block_stmt(block* elem);
stmt* new_while_stmt(expr* cond, stmt* body);
stmt* new_if_stmt(expr* cond, stmt* body, stmt* alter);
stmt* new_declare_stmt(token* type, token* var);
block* new_block(stmt* elem);

void expr_delete(expr* tree);
void expr_list_delete(expr_list* tree);
void stmt_delete(stmt* tree);
void block_delete(block* tree);

void stmt_print(stmt* tree);
void block_print(block* tree);

void expr_print_work(expr* tree, int depth);
void expr_list_print_work(expr_list* tree, int depth);
void stmt_print_work(stmt* tree, int depth);
void block_print_work(block* tree, int depth);

#endif
