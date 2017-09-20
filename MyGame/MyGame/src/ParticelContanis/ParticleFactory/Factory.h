#ifndef FACTORY_H_
#define FACTORY_H_

#include<unordered_map>
#include<memory>
#include<string>

//工場テンプレートクラス
template <class T>
class Factory {
public:
	using ProductPtr = std::shared_ptr<T>;

public:
	//コンストラクタ
	Factory(){}
	//製造の原型を追加
	void add(const std::string& name, const ProductPtr& product) {
		m_ProductContainer[name] = product;
	}
	//製品作成
	ProductPtr create(const std::string& name) const {
		//指定された製品のクローンの生成
		return ProductPtr(m_ProductContainer.at(name)->clone());
	}

private:
	//コピー禁止
	Factory(const Factory& other);
	Factory& operator = (const Factory& other);

private:
	//製品コンテナクラス
	using ProductContainer = std::unordered_map<std::string, ProductPtr>;
	//製品コンテナ
	ProductContainer m_ProductContainer;
};
#endif // !FACTORY_H_
