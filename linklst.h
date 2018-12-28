#ifndef LINKLST_H
#define LINKLST_H
// a generate link list, going to be used by environment
template <typename T>
class List;

template <typename T>
class Link {
	friend class List<T>;
	Link(const T& data)	: m_data(data)
						, m_next(NULL) {
	}
public:
	bool operator==(const T& d) const {
		return m_data == d;
	}
	T Data() {
		return m_data;
	}
private:
	T m_data;
	Link* m_next;
};

//a simple single link list
template <typename T>
class List {
public:
	List() : m_Head(NULL) {
	}
	~List() {
		while(NULL != m_Head)
			m_Head = Rm(m_Head);
	}
	void Add(const T& e) {
		Link<T> *link = new Link<T>(e);
		link->m_next = m_Head;
		m_Head = link;
	}
	Link<T>* Rm(Link<T>* l) {
		Link<T>** p = &m_Head;
		for (; *p != NULL; p = &(*p)->m_next) {
			if ((*p) == l) {
				*p = (*p)->m_next;
				break;
			}
		}
		delete l;
		return *p;
	}
	Link<T>* Head() const {
		return m_Head;
	}
	Link<T>* Next(const Link<T>* l) const {
		return l->m_next;
	}
        int Length() const {
            Link<T>** p = &m_Head;
            int count = 0;
            for(; *p != NULL; p = &(*p)->m_next) {
                count++;
            }
            return count;
        }
private:
	Link<T>* m_Head;
};

#endif