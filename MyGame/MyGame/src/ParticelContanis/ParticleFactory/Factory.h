#ifndef FACTORY_H_
#define FACTORY_H_

#include<unordered_map>
#include<memory>
#include<string>

//�H��e���v���[�g�N���X
template <class T>
class Factory {
public:
	using ProductPtr = std::shared_ptr<T>;

public:
	//�R���X�g���N�^
	Factory(){}
	//�����̌��^��ǉ�
	void add(const std::string& name, const ProductPtr& product) {
		m_ProductContainer[name] = product;
	}
	//���i�쐬
	ProductPtr create(const std::string& name) const {
		//�w�肳�ꂽ���i�̃N���[���̐���
		return ProductPtr(m_ProductContainer.at(name)->clone());
	}

private:
	//�R�s�[�֎~
	Factory(const Factory& other);
	Factory& operator = (const Factory& other);

private:
	//���i�R���e�i�N���X
	using ProductContainer = std::unordered_map<std::string, ProductPtr>;
	//���i�R���e�i
	ProductContainer m_ProductContainer;
};
#endif // !FACTORY_H_
