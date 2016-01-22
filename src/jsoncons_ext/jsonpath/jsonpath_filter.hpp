// Copyright 2013 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_JSONPATH_FILTER_HPP
#define JSONCONS_JSONPATH_FILTER_HPP

#include <string>
#include <sstream>
#include <vector>
#include <istream>
#include <cstdlib>
#include <memory>
#include <regex>
#include "jsoncons/json.hpp"

namespace jsoncons { namespace jsonpath {

template <class Char,class Alloc>
class jsonpath_evaluator;

namespace filter_states {
    enum states_t {
        start,
        cr,
        lf,
        expect_right_round_bracket,
        expect_oper_or_right_round_bracket,
        expect_path_or_value,
        expect_regex,
        regex,
        single_quoted_text,
        double_quoted_text,
        unquoted_text,
        path,
        value,
        oper
    };
}

namespace token_types {
    enum token_types_t {
        left_paren,
        right_paren,
        term,
        eq,
        ne,
        regex,
        ampamp,
        pipepipe,
        lt,
        gt,
        lte,
        gte,
        plus,
        minus,
        exclaim,
        done
    };
}

template<typename Char, class Alloc>
class term
{
public:
    virtual void initialize(const basic_json<Char,Alloc>& context_node)
    {
    }
    virtual bool accept_single_node() const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual basic_json<Char,Alloc> evaluate_single_node() const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool exclaim() const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
	virtual bool eq(const term& rhs) const 
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool eq(const basic_json<Char,Alloc>& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool ne(const term& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool ne(const basic_json<Char,Alloc>& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool regex(const term& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool regex2(const std::basic_string<Char>& subject) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool ampamp(const term& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool ampamp(const basic_json<Char,Alloc>& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool pipepipe(const term& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool pipepipe(const basic_json<Char,Alloc>& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool lt(const term& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool lt(const basic_json<Char,Alloc>& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool gt(const term& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual bool gt(const basic_json<Char,Alloc>& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
	virtual basic_json<Char, Alloc> minus(const term& rhs) const 
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual basic_json<Char,Alloc>  minus(const basic_json<Char,Alloc>& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual basic_json<Char,Alloc>  unary_minus() const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual basic_json<Char,Alloc> plus(const term& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
    virtual basic_json<Char,Alloc>  plus(const basic_json<Char,Alloc>& rhs) const
    {
        throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unsupported_operator, jsonpath_error_category()),1,1);
    }
};

template<typename Char, class Alloc>
class token
{
    token_types::token_types_t type_;
    std::shared_ptr<term<Char,Alloc>> term_;
public:
    token(token_types::token_types_t type)
        : type_(type)
    {
    }
    token(token_types::token_types_t type, std::shared_ptr<term<Char,Alloc>> term)
        : type_(type), term_(term)
    {
    }
    token(const token& t)
        : type_(t.type_), term_(t.term_)
    {
    }

    token_types::token_types_t type() const
    {
        return type_;
    }

    std::shared_ptr<term<Char,Alloc>> term()
    {
        return term_;
    }

    void initialize(const basic_json<Char,Alloc>& context_node)
    {
        if (term_.get() != nullptr)
        {
            term_->initialize(context_node);
        }
    }
};

template<typename Char, class Alloc>
class token_stream
{
    std::vector<token<Char,Alloc>>& tokens_;
    size_t index_;
public:
    token_stream(std::vector<token<Char,Alloc>>& tokens)
        : tokens_(tokens), index_(0)
    {
    }

    token<Char,Alloc> get()
    {
        static token<Char,Alloc> done = token<Char,Alloc>(token_types::done);
        return index_ < tokens_.size() ? tokens_[index_++] : done;
    }
    void putback()
    {
        --index_;
    }
};

template<typename Char, class Alloc>
bool ampamp(const basic_json<Char,Alloc>& lhs, const basic_json<Char,Alloc>& rhs)
{
    return lhs.as_bool() && rhs.as_bool();
}

template<typename Char, class Alloc>
bool pipepipe(const basic_json<Char,Alloc>& lhs, const basic_json<Char,Alloc>& rhs)
{
    return lhs.as_bool() || rhs.as_bool();
}

template<typename Char, class Alloc>
bool lt(const basic_json<Char,Alloc>& lhs, const basic_json<Char,Alloc>& rhs)
{
    bool result = false;
    if (lhs.is<unsigned long long>() && rhs.is<unsigned long long>())
    {
        result = lhs.as<unsigned long long>() < rhs.as<unsigned long long>();
    }
    else if (lhs.is<long long>() && rhs.is<long long>())
    {
        result = lhs.as<long long>() < rhs.as<long long>();
    }
    else if ((lhs.is_number() && rhs.is<double>()) || lhs.is<double>() && rhs.is_number())
    {
        result = lhs.as<double>() < rhs.as<double>();
    }
    else if (lhs.is_string() && rhs.is_string())
    {
        result = lhs.as_string() < rhs.as_string();
    }
    return result;
}

template<typename Char, class Alloc>
bool gt(const basic_json<Char,Alloc>& lhs, const basic_json<Char,Alloc>& rhs)
{
    return lt(rhs,lhs);
}

template<typename Char, class Alloc>
basic_json<Char,Alloc> plus(const basic_json<Char,Alloc>& lhs, const basic_json<Char,Alloc>& rhs)
{
    basic_json<Char,Alloc> result = jsoncons::null_type();
    if (lhs.is<long long>() && rhs.is<long long>())
    {
        result = ((lhs.as<long long>() + rhs.as<long long>()));
    }
    else if ((lhs.is_number() && rhs.is<double>()) || lhs.is<double>() && rhs.is_number())
    {
        result = (lhs.as<double>() + rhs.as<double>());
    }
    else if (lhs.is<unsigned long long>() && rhs.is<unsigned long long>())
    {
        result = (lhs.as<unsigned long long>() + rhs.as<unsigned long long>());
    }
    return result;
}

template<typename Char, class Alloc>
basic_json<Char,Alloc> unary_minus(const basic_json<Char,Alloc>& lhs)
{
    basic_json<Char,Alloc> result = jsoncons::null_type();
    if (lhs.is<long long>())
    {
        result = -lhs.as<long long>();
    }
    else if (lhs.is<double>())
    {
        result = -lhs.as<double>();
    }
    return result;
}

template<typename Char, class Alloc>
basic_json<Char,Alloc> minus(const basic_json<Char,Alloc>& lhs, const basic_json<Char,Alloc>& rhs)
{
    basic_json<Char,Alloc> result = jsoncons::null_type();
    if (lhs.is<long long>() && rhs.is<long long>())
    {
        result = ((lhs.as<long long>() - rhs.as<long long>()));
    }
    else if ((lhs.is_number() && rhs.is<double>()) || lhs.is<double>() && rhs.is_number())
    {
        result = (lhs.as<double>() - rhs.as<double>());
    }
    else if (lhs.is<unsigned long long>() && rhs.is<unsigned long long>() && lt(rhs,lhs))
    {
        result = (lhs.as<unsigned long long>() - rhs.as<unsigned long long>());
    }
    return result;
}

template<typename Char, class Alloc>
class value_term : public term<Char,Alloc>
{
    basic_json<Char,Alloc> value_;
public:
    template <class T>
    value_term(const T& value)
        : value_(value)
    {
    }

    bool accept_single_node() const override
    {
        return value_.as_bool();
    }

    basic_json<Char,Alloc> evaluate_single_node() const override
    {
        return value_;
    }

    bool exclaim() const override
    {
        return !value_.as_bool();
    }

    bool eq(const term<Char,Alloc>& rhs) const override
    {
        return rhs.eq(value_);
    }

    bool eq(const basic_json<Char,Alloc>& rhs) const override
    {
        return value_ == rhs;
    }

    bool ne(const term<Char,Alloc>& rhs) const override
    {
        return rhs.ne(value_);
    }
    bool ne(const basic_json<Char,Alloc>& rhs) const override
    {
        return value_ != rhs;
    }
    bool regex(const term& rhs) const override
    {
        return rhs.regex2(value_.as_string());
    }
    bool ampamp(const term& rhs) const override
    {
        return rhs.ampamp(value_);
    }
    bool ampamp(const basic_json<Char,Alloc>& rhs) const override
    {
        return jsoncons::jsonpath::ampamp(value_,rhs);
    }
    bool pipepipe(const term& rhs) const override
    {
        return rhs.pipepipe(value_);
    }
    bool pipepipe(const basic_json<Char,Alloc>& rhs) const override
    {
        return jsoncons::jsonpath::pipepipe(value_,rhs);
    }

    bool lt(const term<Char,Alloc>& rhs) const override
    {
        return rhs.gt(value_);
    }

    bool lt(const basic_json<Char,Alloc>& rhs) const override
    {
        return jsoncons::jsonpath::lt(value_,rhs);
    }

    bool gt(const term<Char,Alloc>& rhs) const override
    {
        return rhs.lt(value_);
    }

    bool gt(const basic_json<Char,Alloc>& rhs) const override
    {
        return jsoncons::jsonpath::gt(value_,rhs);
    }

    basic_json<Char,Alloc> minus(const term<Char,Alloc>& rhs) const override
    {
        return jsoncons::jsonpath::plus(rhs.unary_minus(),value_);
    }

    basic_json<Char,Alloc> minus(const basic_json<Char,Alloc>& rhs) const override
    {
        return jsoncons::jsonpath::minus(value_,rhs);
    }

    basic_json<Char,Alloc> unary_minus() const override
    {
        return jsoncons::jsonpath::unary_minus(value_);
    }

    basic_json<Char,Alloc> plus(const term<Char,Alloc>& rhs) const override
    {
        return rhs.plus(value_);
    }

    basic_json<Char,Alloc> plus(const basic_json<Char,Alloc>& rhs) const override
    {
        return jsoncons::jsonpath::plus(value_,rhs);
    }
};

template<typename Char, class Alloc>
class regex_term : public term<Char,Alloc>
{
    std::basic_string<Char> pattern_;
    std::regex::flag_type flags_;
public:
    regex_term(const std::basic_string<Char>& pattern, std::regex::flag_type flags)
        : pattern_(pattern), flags_(flags)
    {
    }

    bool regex2(const std::basic_string<Char>& subject) const override
    {
		std::basic_regex<Char> pattern(pattern_,
                                       flags_);
        return std::regex_match(subject, pattern);
    }
};

template<typename Char, class Alloc>
class path_term : public term<Char,Alloc>
{
    std::basic_string<Char> path_;
    basic_json<Char,Alloc> nodes_;
public:
    path_term(const std::basic_string<Char>& path)
        : path_(path)
    {
    }

    void initialize(const basic_json<Char,Alloc>& context_node) override
    {
        jsonpath_evaluator<Char,Alloc> evaluator;
        evaluator.evaluate(context_node,path_);
        nodes_ = evaluator.get_values();
    }

    bool accept_single_node() const override
    {
        return nodes_.size() != 0;
    }

    basic_json<Char,Alloc> evaluate_single_node() const override
    {
        return nodes_.size() == 1 ? nodes_[0] : nodes_;
    }

    bool exclaim() const override
    {
        return nodes_.size() == 0;
    }

    bool eq(const term<Char,Alloc>& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = rhs.eq(nodes_[i]);
            }
        }
        return result;
    }

    bool eq(const basic_json<Char,Alloc>& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = nodes_[i] == rhs;
            }
        }
        return result;
    }

    bool ne(const term& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = rhs.ne(nodes_[i]);
            }
        }
        return result;

    }
    bool ne(const basic_json<Char,Alloc>& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = nodes_[i] != rhs;
            }
        }
        return result;
    }
    bool regex(const term& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = rhs.regex2(nodes_[i].as_string());
            }
        }
        return result;
    }
    bool ampamp(const term& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = rhs.ampamp(nodes_[i]);
            }
        }
        return result;
    }
    bool ampamp(const basic_json<Char,Alloc>& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = jsoncons::jsonpath::ampamp(nodes_[i],rhs);
            }
        }
        return result;
    }
    bool pipepipe(const term& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = rhs.pipepipe(nodes_[i]);
            }
        }
        return result;
    }
    bool pipepipe(const basic_json<Char,Alloc>& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = jsoncons::jsonpath::pipepipe(nodes_[i],rhs);
            }
        }
        return result;
    }

    bool lt(const basic_json<Char,Alloc>& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = jsoncons::jsonpath::lt(nodes_[i],rhs);
            }
        }
        return result;
    }

    bool lt(const term<Char,Alloc>& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = rhs.gt(nodes_[i]);
            }
        }
        return result;
    }

    bool gt(const basic_json<Char,Alloc>& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = jsoncons::jsonpath::gt(nodes_[i],rhs);
            }
        }
        return result;
    }

    bool gt(const term<Char,Alloc>& rhs) const override
    {
        bool result = false;
        if (nodes_.size() > 0)
        {
            result = true;
            for (size_t i = 0; result && i < nodes_.size(); ++i)
            {
                result = rhs.lt(nodes_[i]);
            }
        }
        return result;
    }

    basic_json<Char,Alloc> minus(const basic_json<Char,Alloc>& rhs) const override
    {
        return nodes_.size() == 1 ? jsoncons::jsonpath::minus(nodes_[0],rhs) : jsoncons::null_type();
    }

    basic_json<Char,Alloc> minus(const term<Char,Alloc>& rhs) const override
    {

        return nodes_.size() == 1 ? jsoncons::jsonpath::plus(rhs.unary_minus(),nodes_[0]) : jsoncons::null_type();
    }

    basic_json<Char,Alloc> unary_minus() const override
    {
        return nodes_.size() == 1 ? jsoncons::jsonpath::unary_minus(nodes_[0]) : jsoncons::null_type();
    }

    basic_json<Char,Alloc> plus(const basic_json<Char,Alloc>& rhs) const override
    {
        static auto a_null = jsoncons::null_type();
        return nodes_.size() == 1 ? jsoncons::jsonpath::plus(nodes_[0],rhs) : a_null;
    }

    basic_json<Char,Alloc> plus(const term<Char,Alloc>& rhs) const override
    {
        static auto a_null = jsoncons::null_type();
        return nodes_.size() == 1 ? rhs.plus(nodes_[0]) : a_null;
    }
};

template<typename Char, class Alloc>
class jsonpath_filter_parser
{
    size_t& line_;
    size_t& column_;
    filter_states::states_t state_;
    std::basic_string<Char> buffer_;
    std::vector<token<Char,Alloc>> tokens_;
    int depth_;
    const Char* begin_input_;
    const Char* end_input_;
    const Char*& p_;
    filter_states::states_t pre_line_break_state_;
public:
    jsonpath_filter_parser(const Char** expr, size_t* line,size_t* column)
        : p_(*expr), line_(*line), column_(*column)
    {
    }

    bool exists(const basic_json<Char,Alloc>& context_node)
    {
        for (auto it=tokens_.begin(); it != tokens_.end(); ++it)
        {
            it->initialize(context_node);
        }
        bool result = false;

        token_stream<Char,Alloc> ts(tokens_);
        auto e = expression(ts);
        result = e->accept_single_node();

        return result;
    }

    basic_json<Char,Alloc> eval(const basic_json<Char,Alloc>& context_node)
    {
        try
        {
            for (auto it=tokens_.begin(); it != tokens_.end(); ++it)
            {
                it->initialize(context_node);
            }
       
            token_stream<Char,Alloc> ts(tokens_);
            auto e = expression(ts);
    		basic_json<Char, Alloc> result = e->evaluate_single_node();

            return result;
        }
        catch (const parse_exception& e)
        {
            throw parse_exception(e.code(),line_,column_);
        }
    }

    std::shared_ptr<term<Char,Alloc>> primary(token_stream<Char,Alloc>& ts)
    {
        auto t = ts.get();

        switch (t.type())
        {
        case token_types::left_paren:
		{
			auto expr = expression(ts);
			t = ts.get();
			if (t.type() != token_types::right_paren)
			{
                throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_expected_right_brace, jsonpath_error_category()),line_,column_);
			}
			return expr;
		}
        case token_types::term:
            return t.term();
        case token_types::exclaim:
		{
			basic_json<Char,Alloc> val = primary(ts)->exclaim();
			auto expr = std::make_shared<value_term<Char, Alloc>>(val);
            return expr;
		}
        case token_types::minus:
        {
            basic_json<Char,Alloc> val = primary(ts)->unary_minus();
            auto expr = std::make_shared<value_term<Char, Alloc>>(val);
            return expr;
        }
        default:
            throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_expected_primary, jsonpath_error_category()),line_,column_);
        }
    }

    std::shared_ptr<term<Char,Alloc>> expression(token_stream<Char,Alloc>& ts)
    {
        auto left = term(ts);
        auto t = ts.get();
        while (true)
        {
            switch (t.type())
            {
            case token_types::plus:
			{
				basic_json<Char, Alloc> val = left->plus(*(term(ts)));
				left = std::make_shared<value_term<Char, Alloc>>(val);
				t = ts.get();
			}
                break;
            case token_types::minus:
			{
				basic_json<Char, Alloc> val = left->minus(*(term(ts)));
				left = std::make_shared<value_term<Char, Alloc>>(val);
				t = ts.get();
			}
                break;
            default:
                ts.putback();
                return left;
            }
        }
        return left;
    }

    std::shared_ptr<term<Char,Alloc>> term(token_stream<Char,Alloc>& ts)
    {
        auto left = primary(ts);
        auto t = ts.get();
        while (true)
        {
            switch (t.type())
            {
            case token_types::eq:
            {
                bool e = left->eq(*(primary(ts)));
                basic_json<Char, Alloc> val(e);
                left = std::make_shared<value_term<Char, Alloc>>(val);
                t = ts.get();
            }
                break;
            case token_types::ne:
			{
				bool e = left->ne(*(primary(ts)));
				basic_json<Char, Alloc> val(e);
				left = std::make_shared<value_term<Char, Alloc>>(val);
                t = ts.get();
			}
                break;
            case token_types::regex:
                {
                    bool e = left->regex(*(primary(ts)));
                    basic_json<Char, Alloc> val(e);
                    left = std::make_shared<value_term<Char, Alloc>>(val);
                    t = ts.get();
                }
                break;
            case token_types::ampamp:
                {
                    bool e = left->ampamp(*(primary(ts)));
                    basic_json<Char, Alloc> val(e);
                    left = std::make_shared<value_term<Char, Alloc>>(val);
                    t = ts.get();
                }
                break;
            case token_types::pipepipe:
                {
                    bool e = left->pipepipe(*(primary(ts)));
                    basic_json<Char, Alloc> val(e);
                    left = std::make_shared<value_term<Char, Alloc>>(val);
                    t = ts.get();
                }
                break;
            case token_types::lt:
                {
                    bool e = left->lt(*(primary(ts)));
                    basic_json<Char, Alloc> val(e);
                    left = std::make_shared<value_term<Char, Alloc>>(val);
                    t = ts.get();
                }
                break;
            case token_types::gt:
                {
                    bool e = left->gt(*(primary(ts)));
                    basic_json<Char, Alloc> val(e);
                    left = std::make_shared<value_term<Char, Alloc>>(val);
                    t = ts.get();
                }
                break;
            case token_types::lte:
                {
                    bool e = left->lt(*(primary(ts))) || left->eq(*(primary(ts)));
                    basic_json<Char, Alloc> val(e);
                    left = std::make_shared<value_term<Char, Alloc>>(val);
                    t = ts.get();
                }
                break;
            case token_types::gte:
                {
					bool e = left->gt(*(primary(ts))) || left->eq(*(primary(ts)));
					basic_json<Char, Alloc> val(e);
                    left = std::make_shared<value_term<Char, Alloc>>(val);
                    t = ts.get();
                }
                break;
            default:
                ts.putback();
                return left;
            }
        }
    }

    void parse(const Char* expr, size_t length)
    {
        parse(expr,expr+length);
    }

    void parse(const Char* expr, const Char* end_expr)
    {
        p_ = expr;
        end_input_ = end_expr;
        depth_ = 0;
        tokens_.clear();
        state_ = filter_states::start;
        bool done = false;
        while (!done && p_ < end_input_)
        {
            switch (state_)
            {
            case filter_states::cr:
                ++line_;
                column_ = 1;
                switch (*p_)
                {
                case '\n':
                    state_ = pre_line_break_state_;
                    ++p_;
                    ++column_;
                    break;
                default:
                    state_ = pre_line_break_state_;
                    break;
                }
                break;
            case filter_states::lf:
                ++line_;
                column_ = 1;
                state_ = pre_line_break_state_;
                break;
            case filter_states::start:
                switch (*p_)
                {
                case '\r':
                    pre_line_break_state_ = state_;
                    state_ = filter_states::cr;
                    break;
                case '\n':
                    pre_line_break_state_ = state_;
                    state_ = filter_states::lf;
                    break;
                case '(':
                    state_ = filter_states::expect_path_or_value;
                    ++depth_;
                    tokens_.push_back(token<Char,Alloc>(token_types::left_paren));
                    break;
                case ')':
                    tokens_.push_back(token<Char,Alloc>(token_types::right_paren));
                    if (--depth_ == 0)
                    {
                        done = true;
                    }
                    break;
                }
                ++p_;
                ++column_;
                break;
            case filter_states::oper:
                switch (*p_)
                {
                case filter_states::cr:
                    ++line_;
                    column_ = 1;
                    switch (*p_)
                    {
                    case '\n':
                        state_ = pre_line_break_state_;
                        ++p_;
                        ++column_;
                        break;
                    default:
                        state_ = pre_line_break_state_;
                        break;
                    }
                    break;
                case filter_states::lf:
                    ++line_;
                    column_ = 1;
                    state_ = pre_line_break_state_;
                    break;
                case '!':
                    if (p_+1  < end_input_ && *(p_+1) == '=')
                    {
                        ++p_;
                        ++column_;
                        state_ = filter_states::expect_path_or_value;
                        tokens_.push_back(token<Char,Alloc>(token_types::ne));
                    }
        		    else
        		    {
        		    	state_ = filter_states::expect_path_or_value;
        		    	tokens_.push_back(token<Char, Alloc>(token_types::exclaim));
        		    }
                    break;
                case '&':
                    if (p_+1  < end_input_ && *(p_+1) == '&')
                    {
                        ++p_;
                        ++column_;
                        state_ = filter_states::expect_path_or_value;
                        tokens_.push_back(token<Char,Alloc>(token_types::ampamp));
                    }
                    break;
                case '|':
                    if (p_+1  < end_input_ && *(p_+1) == '|')
                    {
                        ++p_;
                        ++column_;
                        state_ = filter_states::expect_path_or_value;
                        tokens_.push_back(token<Char,Alloc>(token_types::pipepipe));
                    }
                    break;
                case '=':
                    if (p_+1  < end_input_ && *(p_+1) == '=')
                    {
                        ++p_;
                        ++column_;
                        state_ = filter_states::expect_path_or_value;
                        tokens_.push_back(token<Char,Alloc>(token_types::eq));
                    }
                    else if (p_+1  < end_input_ && *(p_+1) == '~')
                    {
                        ++p_;
                        ++column_;
                        state_ = filter_states::expect_regex;
                        tokens_.push_back(token<Char,Alloc>(token_types::regex));
                    }
                    break;
                case '>':
                    if (p_+1  < end_input_ && *(p_+1) == '=')
                    {
                        ++p_;
                        ++column_;
                        state_ = filter_states::expect_path_or_value;
                        tokens_.push_back(token<Char,Alloc>(token_types::gte));
                    }
                    else
                    {
                        state_ = filter_states::expect_path_or_value;
                        tokens_.push_back(token<Char,Alloc>(token_types::gt));
                    }
                    break;
                case '<':
                    if (p_+1  < end_input_ && *(p_+1) == '=')
                    {
                        ++p_;
                        ++column_;
                        state_ = filter_states::expect_path_or_value;
                        tokens_.push_back(token<Char,Alloc>(token_types::lte));
                    }
                    else
                    {
                        state_ = filter_states::expect_path_or_value;
                        tokens_.push_back(token<Char,Alloc>(token_types::lt));
                    }
                    break;
                case '+':
                    state_ = filter_states::expect_path_or_value;
                    tokens_.push_back(token<Char,Alloc>(token_types::plus));
                    break;
                case '-':
                    state_ = filter_states::expect_path_or_value;
                    tokens_.push_back(token<Char,Alloc>(token_types::minus));
                    break;
                case ' ':case '\t':
                    break;
                default:
                    throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter, jsonpath_error_category()),line_,column_);
                    break;

                }
                ++p_;
                ++column_;
                break;
            case filter_states::unquoted_text: 
                {
                    switch (*p_)
                    {
                    case filter_states::cr:
                        ++line_;
                        column_ = 1;
                        switch (*p_)
                        {
                        case '\n':
                            state_ = pre_line_break_state_;
                            ++p_;
                            ++column_;
                            break;
                        default:
                            state_ = pre_line_break_state_;
                            break;
                        }
                        break;
                    case filter_states::lf:
                        ++line_;
                        column_ = 1;
                        state_ = pre_line_break_state_;
                        break;
                    case '<':
                    case '>':
                    case '!':
                    case '=':
                    case '&':
                    case '|':
                    case '+':
                    case '-':
                        {
                            if (buffer_.length() > 0)
                            {
                                try
                                {
                                    auto val = basic_json<Char, Alloc>::parse(buffer_);
                                    tokens_.push_back(token<Char,Alloc>(token_types::term,std::make_shared<value_term<Char, Alloc>>(val)));
                                }
                                catch (const parse_exception& e)
                                {
                                    throw parse_exception(e.code(),line_,column_);
                                }
                                buffer_.clear();
                            }
                            state_ = filter_states::oper;
                        }
                        break;
                    case ')':
                        if (buffer_.length() > 0)
                        {
                            try
                            {
                                auto val = basic_json<Char,Alloc>::parse(buffer_);
                                tokens_.push_back(token<Char,Alloc>(token_types::term,std::make_shared<value_term<Char, Alloc>>(val)));
                            }
                            catch (const parse_exception& e)
                            {
                                throw parse_exception(e.code(),line_,column_);
                            }
                            buffer_.clear();
                        }
                        tokens_.push_back(token<Char,Alloc>(token_types::right_paren));
						if (--depth_ == 0)
						{
                            state_ = filter_states::start;
                            done = true;
						}
                        else
                        {
                            state_ = filter_states::expect_path_or_value;
                        }
                        ++p_;
                        ++column_;
                        break;
                    case ' ':case '\t':
                        if (buffer_.length() > 0)
						{
                            try
                            {
                                auto val = basic_json<Char,Alloc>::parse(buffer_);
                                tokens_.push_back(token<Char,Alloc>(token_types::term,std::make_shared<value_term<Char, Alloc>>(val)));
                            }
                            catch (const parse_exception& e)
                            {
                                throw parse_exception(e.code(),line_,column_);
                            }
							buffer_.clear();
						}
                        ++p_;
                        ++column_;
                        break; 
                    default: 
                        buffer_.push_back(*p_);
                        ++p_;
                        ++column_;
                        break;
                    }
                }
                break;
            case filter_states::single_quoted_text: 
                {
                    switch (*p_)
                    {                   
                    case filter_states::cr:
                        ++line_;
                        column_ = 1;
                        switch (*p_)
                        {
                        case '\n':
                            state_ = pre_line_break_state_;
                            ++p_;
                            ++column_;
                            break;
                        default:
                            state_ = pre_line_break_state_;
                            break;
                        }
                        break;
                    case filter_states::lf:
                        ++line_;
                        column_ = 1;
                        state_ = pre_line_break_state_;
                        break;
                    case '\\':
                        buffer_.push_back(*p_);
                        if (p_+1 < end_input_)
                        {
                            ++p_;
                            ++column_;
                            buffer_.push_back(*p_);
                        }
                        break;
                    case '\'':
                        buffer_.push_back('\"');
                        //if (buffer_.length() > 0)
                        {
                            try
                            {
                                auto val = basic_json<Char,Alloc>::parse(buffer_);
                                tokens_.push_back(token<Char,Alloc>(token_types::term,std::make_shared<value_term<Char, Alloc>>(val)));
                            }
                            catch (const parse_exception& e)
                            {
                                throw parse_exception(e.code(),line_,column_);
                            }
                            buffer_.clear();
                        }
						state_ = filter_states::expect_path_or_value;
                        break;

                    default: 
                        buffer_.push_back(*p_);
                        break;
                    }
                }
                ++p_;
                ++column_;
                break;
            case filter_states::double_quoted_text: 
                {
                    switch (*p_)
                    {                   
                    case filter_states::cr:
                        ++line_;
                        column_ = 1;
                        switch (*p_)
                        {
                        case '\n':
                            state_ = pre_line_break_state_;
                            ++p_;
                            ++column_;
                            break;
                        default:
                            state_ = pre_line_break_state_;
                            break;
                        }
                        break;
                    case filter_states::lf:
                        ++line_;
                        column_ = 1;
                        state_ = pre_line_break_state_;
                        break;
                    case '\\':
                        buffer_.push_back(*p_);
                        if (p_+1 < end_input_)
                        {
                            ++p_;
                            ++column_;
                            buffer_.push_back(*p_);
                        }
                        break;
                    case '\"':
                        buffer_.push_back(*p_);
                        //if (buffer_.length() > 0)
                        {
                            try
                            {
                                auto val = basic_json<Char,Alloc>::parse(buffer_);
                                tokens_.push_back(token<Char,Alloc>(token_types::term,std::make_shared<value_term<Char, Alloc>>(val)));
                            }
                            catch (const parse_exception& e)
                            {
                                throw parse_exception(e.code(),line_,column_);
                            }
                            buffer_.clear();
                        }
                        state_ = filter_states::expect_path_or_value;
                        break;

                    default: 
                        buffer_.push_back(*p_);
                        break;
                    }
                }
                ++p_;
                ++column_;
                break;
            case filter_states::expect_path_or_value: 
                switch (*p_)
                {
                case filter_states::cr:
                    ++line_;
                    column_ = 1;
                    switch (*p_)
                    {
                    case '\n':
                        state_ = pre_line_break_state_;
                        ++p_;
                        ++column_;
                        break;
                    default:
                        state_ = pre_line_break_state_;
                        break;
                    }
                    break;
                case filter_states::lf:
                    ++line_;
                    column_ = 1;
                    state_ = pre_line_break_state_;
                    break;
                case '<':
                case '>':
                case '!':
                case '=':
                case '&':
                case '|':
                case '+':
                case '-':
                    state_ = filter_states::oper;
                    // don't increment
                    break;
                case '@':
                    buffer_.push_back(*p_);
                    state_ = filter_states::path;
                    ++p_;
                    ++column_;
                    break;
				case ' ':case '\t':
                    ++p_;
                    ++column_;
					break;
                case '\'':
                    buffer_.push_back('\"');
                    state_ = filter_states::single_quoted_text;
                    ++p_;
                    ++column_;
                    break;
                case '\"':
                    buffer_.push_back(*p_);
                    state_ = filter_states::double_quoted_text;
                    ++p_;
                    ++column_;
                    break;
                case '(':
                    ++depth_;
                    tokens_.push_back(token<Char,Alloc>(token_types::left_paren));
                    ++p_;
                    ++column_;
                    break;
                case ')':
                    tokens_.push_back(token<Char,Alloc>(token_types::right_paren));
                    if (--depth_ == 0)
                    {
                        done = true;
                        state_ = filter_states::start;
                    }
                    ++p_;
                    ++column_;
                    break;
                default: 
                    // don't increment
                    state_ = filter_states::unquoted_text;
                    break;
                };
                break;
            case filter_states::expect_oper_or_right_round_bracket: 
                switch (*p_)
                {
                case filter_states::cr:
                    ++line_;
                    column_ = 1;
                    switch (*p_)
                    {
                    case '\n':
                        state_ = pre_line_break_state_;
                        ++p_;
                        ++column_;
                        break;
                    default:
                        state_ = pre_line_break_state_;
                        break;
                    }
                    break;
                case filter_states::lf:
                    ++line_;
                    column_ = 1;
                    state_ = pre_line_break_state_;
                    break;
                case ' ':case '\t':
                    break;
                case ')':
                    tokens_.push_back(token<Char,Alloc>(token_types::right_paren));
                    if (--depth_ == 0)
                    {
                        done = true;
                        state_ = filter_states::start;
                    }
                    break;
                case '<':
                case '>':
                case '!':
                case '=':
                case '&':
                case '|':
                case '+':
                case '-':
                    {
                        state_ = filter_states::oper;
                        // don't increment p
                    }
                    break;
                default: 
                    throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter, jsonpath_error_category()),line_,column_);
                    break;
                };
                break;
            case filter_states::expect_right_round_bracket: 
                switch (*p_)
                {
                case filter_states::cr:
                    ++line_;
                    column_ = 1;
                    switch (*p_)
                    {
                    case '\n':
                        state_ = pre_line_break_state_;
                        ++p_;
                        ++column_;
                        break;
                    default:
                        state_ = pre_line_break_state_;
                        break;
                    }
                    break;
                case filter_states::lf:
                    ++line_;
                    column_ = 1;
                    state_ = pre_line_break_state_;
                    break;
                case ' ':case '\t':
                    break;
                case ')':
                    tokens_.push_back(token<Char,Alloc>(token_types::right_paren));
                    if (--depth_ == 0)
                    {
                        done = true;
                        state_ = filter_states::start;
                    }
                    else 
                    {
                        state_ = filter_states::expect_oper_or_right_round_bracket;
                    }
                    break;
                default: 
                    throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter, jsonpath_error_category()),line_,column_);
                    break;
                };
                ++p_;
                ++column_;
                break;
            case filter_states::path: 
                switch (*p_)
                {
                case filter_states::cr:
                    ++line_;
                    column_ = 1;
                    switch (*p_)
                    {
                    case '\n':
                        state_ = pre_line_break_state_;
                        ++p_;
                        ++column_;
                        break;
                    default:
                        state_ = pre_line_break_state_;
                        break;
                    }
                    break;
                case filter_states::lf:
                    ++line_;
                    column_ = 1;
                    state_ = pre_line_break_state_;
                    break;
                case '<':
                case '>':
                case '!':
                case '=':
                case '&':
                case '|':
                case '+':
                case '-':
                    {
                        if (buffer_.length() > 0)
                        {
                            tokens_.push_back(token<Char,Alloc>(token_types::term,std::make_shared<path_term<Char,Alloc>>(buffer_)));
                            buffer_.clear();
                        }
                        state_ = filter_states::oper;
                        // don't increment
                    }
                    break;
                case ')':
                    if (buffer_.length() > 0)
                    {
                        tokens_.push_back(token<Char,Alloc>(token_types::term,std::make_shared<path_term<Char,Alloc>>(buffer_)));
                        tokens_.push_back(token<Char,Alloc>(token_types::right_paren));
                        buffer_.clear();
                    }
                    if (--depth_ == 0)
                    {
                        state_ = filter_states::start;
                        done = true;
                    }
                    else
                    {
                        state_ = filter_states::expect_path_or_value;
                    }
                    ++p_;
                    ++column_;
                    break;
                default:
                    buffer_.push_back(*p_);
                    ++p_;
                    ++column_;
                    break;
                };
                break;
            case filter_states::expect_regex: 
                switch (*p_)
                {
                case filter_states::cr:
                    ++line_;
                    column_ = 1;
                    switch (*p_)
                    {
                    case '\n':
                        state_ = pre_line_break_state_;
                        ++p_;
                        ++column_;
                        break;
                    default:
                        state_ = pre_line_break_state_;
                        break;
                    }
                    break;
                case filter_states::lf:
                    ++line_;
                    column_ = 1;
                    state_ = pre_line_break_state_;
                    break;
                case '/':
                    state_ = filter_states::regex;
                    break;
                case ' ':case '\t':
                    break;
                default: 
                    throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_expected_slash, jsonpath_error_category()),line_,column_);
                    break;
                };
                ++p_;
                ++column_;
                break;
            case filter_states::regex: 
                {
                    switch (*p_)
                    {                   
                    case filter_states::cr:
                        ++line_;
                        column_ = 1;
                        switch (*p_)
                        {
                        case '\n':
                            state_ = pre_line_break_state_;
                            ++p_;
                            ++column_;
                            break;
                        default:
                            state_ = pre_line_break_state_;
                            break;
                        }
                        break;
                    case filter_states::lf:
                        ++line_;
                        column_ = 1;
                        state_ = pre_line_break_state_;
                        break;
                    case '/':
                        //if (buffer_.length() > 0)
                        {
                            std::regex::flag_type flags = std::regex_constants::ECMAScript; 
                            if (p_+1  < end_input_ && *(p_+1) == 'i')
                            {
                                ++p_;
                                ++column_;
                                flags |= std::regex_constants::icase;
                            }
                            tokens_.push_back(token<Char,Alloc>(token_types::term,std::make_shared<regex_term<Char, Alloc>>(buffer_,flags)));
                            buffer_.clear();
                        }
                        state_ = filter_states::expect_path_or_value;
                        break;

                    default: 
                        buffer_.push_back(*p_);
                        break;
                    }
                }
                ++p_;
                ++column_;
                break;
            default:
                ++p_;
                ++column_;
                break;
            }
        }
        if (depth_ != 0)
        {
            throw parse_exception(std::error_code(jsonpath_parser_errc::invalid_filter_unbalanced_paren, jsonpath_error_category()),line_,column_);
        }
    }
};


}}
#endif