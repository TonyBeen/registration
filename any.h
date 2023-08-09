/*************************************************************************
    > File Name: any.h
    > Author: hsz
    > Brief:
    > Created Time: Sat 05 Aug 2023 01:19:58 PM CST
 ************************************************************************/

#ifndef __UTILS_ANY_HPP__
#define __UTILS_ANY_HPP__

#include <typeinfo>
#include <utility>

class any {
public:
    any() : content_(nullptr) {}
    ~any() {
        if (content_) {
            delete content_;
        }
    }

    template<typename ValueType>
    explicit any(const ValueType& value)
        : content_(new Holder<ValueType>(value)) {}

    any(const any& rhs)
        : content_(rhs.content_ ? rhs.content_->clone() : nullptr) {}

public:
    any& swap(any& rhs) {
        std::swap(content_, rhs.content_);
        return *this;
    }

    template<typename ValueType>
    any& operator=(const ValueType& rhs) {
        any(rhs).swap(*this);
        return *this;
    }

    any& operator=(const any& rhs) {
        any(rhs).swap(*this);
        return *this;
    }

    bool empty() const {
        return !content_;
    }

    const std::type_info& type() const {
        return content_ ? content_->getType() : typeid(void);
    }

    template<typename ValueType>
    ValueType operator()() const {
        if (content_->getType() == typeid(ValueType)) {
            return static_cast<any::Holder<ValueType>*>(content_)->held_;
        } else {
            return ValueType();
        }
    }

protected:
    class PlaceHolder {
    public:
        virtual ~PlaceHolder() {}
    public:
        virtual const std::type_info& getType() const = 0;
        virtual PlaceHolder* clone() const = 0;
    };

    template<typename ValueType>
    class Holder : public PlaceHolder {
    public:
        Holder(const ValueType& value)
            : held_(value) {}

        virtual const std::type_info& getType() const {
            return typeid(ValueType);
        }

        virtual PlaceHolder* clone() const {
            return new Holder(held_);
        }

        ValueType held_;
    };

protected:
    PlaceHolder* content_;

    template<typename ValueType>
    friend ValueType* any_cast(any*);
};

template<typename ValueType>
ValueType* any_cast(any* any) {
    if (any && any->type() == typeid(ValueType)) {
        return &(static_cast<any::Holder<ValueType> *>(any->content_)->held_);
    }

    return nullptr;
}

template<typename ValueType>
const ValueType *any_cast(const any* anyPtr) {
    return any_cast<ValueType>(const_cast<any *>(anyPtr));
}

template<typename ValueType>
ValueType any_cast(const any& any) {
    const ValueType *result = any_cast<ValueType>(&any);

    if (!result) {
        return ValueType();
    }

    return *result;
}

#endif // __UTILS_ANY_HPP__