#include <iostream>
#include <fstream>

using namespace std;


//������� 23, �������
template <class T>
class Element
{
	//������� �������� ������
private:
	//��������� �� ���������� � ��������� �������
	Element* next;
	Element* prev;
	//����������, �������� � ����
	T field;
public:
	Element(T value, Element<T> *next_ptr = NULL, Element<T> *prev_ptr = NULL)
	{
		field = value;
		next = next_ptr;
		prev = prev_ptr;
	}
	Element()
	{
		next = this;
		prev = this;
	}
	//������ � ���� *next
	virtual Element* getNext() { return next; }

	virtual void setNext(Element* value) { next = value; }

	//������ � ���� *prev
	virtual Element* getPrevious() { return prev; }

	virtual void setPrevious(Element* value) { prev = value; }

	//������ � ���� � �������� ����������� field
	virtual T getValue() { return field; }

	virtual void setValue(T value) { field = value; }

	template<class T> friend ostream& operator<< (ostream &ustream, Element<T> &obj);
};

template<class T>
ostream& operator << (ostream& ustream, Element<T>& obj)
{
	ustream << "\n" << obj.field;
	return ustream;
}

template <class T>
class LinkedListParent
{
protected:
	//���������� ������� ������ � �����
	Element<T>* head;
	Element<T>* tail;
	//��� �������� ������ ���������� ���������
	int num;
public:
	virtual int Number() { return num; }
	virtual Element<T>* getBegin()
	{
		return head;
	}
	void setBegin(Element<T>* value)
	{
		head = value;
	}
	virtual Element<T>* getEnd() 
	{
		return tail;
	}
	void setEnd(Element<T>* value)
	{
		tail = value;
	}
	LinkedListParent()
	{
		//����������� ��� ����������
		cout << "\nParent constructor";
		Element<T> *firstElement = new Element<T>();

		head = firstElement;
		tail = firstElement;
		num = 1;
	}
	//����� ����������� �������: ���� �� ����������� � ����� ������,�� ������ ����������� ����������
		virtual Element<T>* push(T value) = 0;
	//����� ����������� �������: ���� �� ����������� � �����������, �� ������ ����������� ��������
		virtual Element<T>* pop() = 0;
	virtual ~LinkedListParent()
	{
		//���������� - ������������ ������
		cout << "\nParent destructor";
	}

	//��������� �������� �� ������� - ������ ��������������� ������ ����� �������� ?
		virtual Element<T>*operator[](int i)
	{
		//����������
		if (i<0 || i>num) return NULL;
		int k = 0;
		//���� i-� ������� - ������� � ������ � ����������� i ����� ������
			Element<T>* cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}

	template<class T> friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj);
	template<class T> friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T> &obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); current !=
			NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}
	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL;
		current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue()
		<< "\n";
	return ustream;
}

template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{
	//������ �� ����� � ������� ���������
	int len;
	ustream >> len;
	//����� ���� �������� ������ ��� obj, ���������� obj.num = 0
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:
public:
	ListIterator() { ptr = NULL; }

	//ListIterator(ValueType* p) { ptr = p; }
	ListIterator(Element<ValueType>* p) { ptr = p; }

	ListIterator(const ListIterator& it) { ptr = it.ptr; }

	bool operator!=(ListIterator const& other) const {
		return ptr != other.ptr;
	}

	bool operator==(ListIterator const& other) const {
		return
			ptr == other.ptr;
	}

	//need for BOOST_FOREACH
	Element<ValueType>& operator*()
	{
		return *ptr;
	}
	ListIterator& operator++() {
		ptr = ptr->getNext();
		return *this;
	}
	ListIterator& operator++(int v) {
		ptr = ptr->getNext();
		return *this;
	}
	ListIterator& operator=(const ListIterator& it) {
		ptr = it.ptr;
		return *this;
	}
	ListIterator& operator=(Element<ValueType>* p) {
		ptr = p;
		return *this;
	}
private:
	Element<ValueType>* ptr;
};

template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:

	IteratedLinkedList() : LinkedListParent<T>()
	{
		cout << "\nIteratedLinkedList constructor";
	}
	virtual ~IteratedLinkedList()
	{
		cout << "\nIteratedLinkedList destructor";
	}
	ListIterator<T> iterator;
	ListIterator<T> begin()
	{
		ListIterator<T> it = LinkedListParent<T>::head; return it;
		
	}
	ListIterator<T> end()
	{
		ListIterator<T> it = LinkedListParent<T>::tail; return it;
	}
};

template <class T>
class D : public IteratedLinkedList<T>
{
private:

protected:

public:
	using LinkedListParent<T>::getEnd;
	using LinkedListParent<T>::setEnd;
	using LinkedListParent<T>::getBegin;
	using LinkedListParent<T>::setBegin;
	using LinkedListParent<T>::num;

	Element<T>* push(T value)
	{
		Element<T> newElem(value);
		newElem.setPrevious(getEnd());
		getEnd()->setNext(&newElem);
		setEnd(&newElem);
		num++;
		return &newElem;
	}

	/// <returns>deleted element</returns>
	Element<T>* pop()
	{
		Element<T>& secondElem = *getBegin()->getNext();
		setBegin(nullptr);
		setBegin(&secondElem);
		secondElem.setPrevious(nullptr);
		return new Element<T>;
	}
};


//��������� ��������� ������ D.�������������� ������� ����������
//������ �������� ����� �������, ����� ��������� ��������� �������������. ����������� �� ������ ��������???
template <class T>
class AdvancedD : D<T> 
{
private:
protected:
public:
	Element<T>* push(T value)
	{

	}
	
};





int main()
{
	D<int> obj;
	obj.push(110);

	ListIterator<int> iter(obj.begin());
	for (int i = 1; i < 6; i++)
	{
		obj.push(i);
		//cout << *iter;
		//iter++;
	}
	

	
	return 0;
}