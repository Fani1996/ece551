#include <string>
#include <sstream>

class Expression {
public:
	virtual std::string toString() const = 0;
	virtual long evaluate() const = 0;
	virtual ~Expression() {}
};

class NumExpression : public Expression {
	long numVal;
public:
	NumExpression(long v) : numVal(v) {}
	virtual std::string toString() const {
		std::stringstream ss;
		ss << numVal;
		return ss.str();
	}
	virtual long evaluate() const {
		return numVal;
	}
};

class BinOpExpression : public Expression {
protected:
	const char *theOp; // always points to a literal
	Expression *lhs, *rhs; // owned by the object
public:
	BinOpExpression(const char *op, Expression *lhs, Expression *rhs) : theOp(op), lhs(lhs), rhs(rhs) {}
	virtual std::string toString() const {
		std::stringstream ss;
		ss << '(' << lhs->toString() << ' ' << theOp << ' ' << rhs->toString() << ')';
		return ss.str();
	}
	virtual ~BinOpExpression() {
		delete lhs;
		delete rhs;
	}
};

class PlusExpression : public BinOpExpression {
public:
	PlusExpression(Expression *lhs, Expression *rhs) : BinOpExpression("+", lhs, rhs) {}
	virtual long evaluate() const {
		return lhs->evaluate() + rhs->evaluate();
	}
};

class MinusExpression : public BinOpExpression {
public:
	MinusExpression(Expression *lhs, Expression *rhs) : BinOpExpression("-", lhs, rhs) {}
	virtual long evaluate() const {
		return lhs->evaluate() - rhs->evaluate();
	}
};

class TimesExpression : public BinOpExpression {
public:
	TimesExpression(Expression *lhs, Expression *rhs) : BinOpExpression("*", lhs, rhs) {}
	virtual long evaluate() const {
		return lhs->evaluate() * rhs->evaluate();
	}
};

class DivExpression : public BinOpExpression {
public:
	DivExpression(Expression *lhs, Expression *rhs) : BinOpExpression("/", lhs, rhs) {}
	virtual long evaluate() const {
		return lhs->evaluate() / rhs->evaluate();
	}
};
