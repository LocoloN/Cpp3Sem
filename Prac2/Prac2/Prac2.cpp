#include <iostream>
#include <fstream>

using namespace std;




class looseElementException : exception
{
	virtual const char* what() const
	{
		return "Iterator is not associated with any element";
	}

};

//������� 21, �������
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
	Element(T value = NULL, Element<T> *next_ptr = NULL, Element<T> *prev_ptr = NULL)
	{
		field = value;
		next = next_ptr;
		prev = prev_ptr;
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
	virtual Element<T>* getEnd() 
	{
		return tail;
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
	LinkedListParent(T val)
	{
		Element<T>* firstElement = new Element<T>(val);
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

	Element<ValueType>& getValue()
	{
		(!ptr) ? throw looseElementException():void();
		return *ptr;
	}

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
	ListIterator& operator--() {
		ptr = ptr->getPrevious();
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
	IteratedLinkedList(T val) : LinkedListParent<T>(val)
	{

	}
	virtual ~IteratedLinkedList()
	{
		cout << "\nIteratedLinkedList destructor";
	}

	ListIterator<T> iterator;

	ListIterator<T> begin()
	{
		ListIterator<T> it = LinkedListParent<T>::head;
		return it;
		
	}
	ListIterator<T> end()
	{
		ListIterator<T> it = LinkedListParent<T>::tail; 
		return it;
	}
};

template <class T>
class D : public IteratedLinkedList<T>
{
private:

protected:

public:
	using LinkedListParent<T>::getEnd;
	using LinkedListParent<T>::getBegin;
	using LinkedListParent<T>::head;
	using LinkedListParent<T>::tail;
	using LinkedListParent<T>::num;

	D(T val) : IteratedLinkedList<T>(val)
	{

	}
	Element<T>* push(T value)
	{
		/*
		Element<T> newElem(value);
		Element<T>* endElem = getEnd();
		newElem.setPrevious(endElem);
		endElem->setNext(&newElem);
		tail = &newElem;*/

		Element<T>* newElem = new Element<T>(value);
		Element<T>* endElem = getEnd();
		newElem->setPrevious(endElem);
		endElem->setNext(newElem);
		tail = newElem;
		num++;
		return newElem;
	}
	/// <summary>
	/// inserts element afret iterated
	/// </summary>
	/// <param name="val">new element value</param>
	/// <param name="iter">iterator</param>
	/// <returns>pushed new element</returns>
	Element<T>* push(const T& val, ListIterator<T>* iter)
	{
		Element<T>* newElem = new Element<T>(val);
		Element<T>* itElem = &iter->getValue();

		newElem->setPrevious(itElem);
		newElem->setNext(itElem->getNext());
		itElem->setNext(newElem);
		itElem->getNext()->setPrevious(newElem);
		num++;
		return newElem;
	}

	/// <returns>deleted element</returns>
	Element<T>* pop()
	{
		Element<T>* deletedElem = getBegin();
		if (!getBegin()->getNext())
		{
			delete getBegin();
			head = NULL;
			tail = NULL;
			return deletedElem;
		}
		Element<T>* secondElem = getBegin()->getNext();
		delete(head);
		head = secondElem;
		secondElem->setPrevious(nullptr);
		num--;
		return deletedElem;
	}
};
template <typename T>
IteratedLinkedList<T>* filter(IteratedLinkedList<T> *obj, bool (*P)(Element<T>))
{
	D<T> *processedList = obj;
	IteratedLinkedList<T>* resultList;

	processedList->iterator = processedList->begin();

	while (processedList->iterator.getValue().getNext())
	{
		(P(processedList->iterator.getValue())) ? resultList->push(processedList->iterator.getValue()) :void() ;
	}
	resultList->pop();
	return resultList();
}

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

template <typename T>
void displayList(D<T> *obj)
{
	obj.iterator = obj.begin();
	for (int i = 0; i < obj.num; i++)
	{
		cout << obj.iterator.getValue();
		obj.iterator++;
	}
}


bool test()
{
	return true;
}

int main()
{
	D<int> obj(110);

	for (int i = 1; i < 5; i++)
	{
		obj.push(i);
	}
	obj.pop();
	obj.iterator = obj.begin();
	for (int i = 0; i < obj.num; i++)
	{
		cout << obj.iterator.getValue();
		obj.iterator++;
	}
	cout << "\n\n\n";

	obj.iterator = obj.end();

	--obj.iterator;
	int x = 123;
	obj.push(x, &obj.iterator);
	
	obj.iterator = obj.begin();
	for (int i = 0; i < obj.num; i++)
	{
		cout << obj.iterator.getValue();
		obj.iterator++;
	}


	return 0;
}