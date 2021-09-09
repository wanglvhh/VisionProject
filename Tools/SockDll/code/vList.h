#ifndef __VLIST_H__
#define __VLIST_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vCriticalSection.h"
/////////////////////////////////////////////////////////////////////
/*******************************************************************\
	��vListArg����������������,���нڵ����T��߱���ֵ������
	��vListPtr����ָ����������,���нڵ����T���ڴ�������ͷ�
		���ⲿ������T��߱��������캯��(ʹ���д���ĳ�̶ֳȵ�����)
	Designed By  Vinca!
										2002.12
\*******************************************************************/
#define V_MAX_LIST_COUNTS_DEFAULT		1024
#define V_MAX_LIST_COUNTS_LIMIT			65535
/////////////////////////////////////////////////
template<class T> class vListPtr;

template<class T>
class vListNodePtr
{
	friend class vListPtr<T>;
private:
	vListNodePtr(T* _data){
		m_pData=_data;
		m_pNext=m_pPrev=NULL;
		m_dwPos=0;
	}
	~vListNodePtr(){}
	T* m_pData;
	vListNodePtr<T>* m_pPrev;//ָ��ǰ��ڵ�
	vListNodePtr<T>* m_pNext;//ָ�����ڵ�
	DWORD m_dwPos;//��ʾ���ڵ��������е�λ��(��ֵΪ��)
};

template<class T>
class vListPtr
{
public:
	BOOL IsEmpty() const
	{
		VCriticalSection myCric(&m_nCriticalSection);
		return (m_dwCurCounts==0);
	}
	BOOL IsFull() const
	{
		VCriticalSection myCric(&m_nCriticalSection);
		return (m_dwCurCounts==m_dwMaxCounts);
	}
	DWORD GetCurCounts() const
	{
		VCriticalSection myCric(&m_nCriticalSection);
		return m_dwCurCounts;
	}
	DWORD GetMaxCountsLimits() const
	{
		VCriticalSection myCric(&m_nCriticalSection);
		return m_dwMaxCounts;
	}
	BOOL InsertAfterTail(T* data)
	{
		VCriticalSection myCric(&m_nCriticalSection);
		if( (m_dwCurCounts+1)>m_dwMaxCounts )
			return FALSE;
		vListNodePtr<T>* _node=new vListNodePtr<T>(data);
		if( _node==NULL ) return FALSE;
		_node->m_pPrev=m_pTail;
		if( m_pTail )
		{
			m_pTail->m_pNext=_node;
			_node->m_dwPos=m_pTail->m_dwPos+1;//����λ����Ϣ
		}
		m_pTail=_node;
		if( m_dwCurCounts==0 )
		{//��ǰΪ������
			m_pHead=m_pVisit=m_pTail;
		}
		m_dwCurCounts++;
		return TRUE;
	}
	BOOL InsertBeforeHead(T* data)
	{
		VCriticalSection myCric(&m_nCriticalSection);
		if( (m_dwCurCounts+1)>m_dwMaxCounts )
			return FALSE;
		vListNodePtr<T>* _node=new vListNodePtr<T>(data);
		if( _node==NULL ) return FALSE;
		//����λ����Ϣ
		vListNodePtr<T>* tmp=m_pHead;
		while( tmp )
		{
			tmp->m_dwPos++;
			tmp=tmp->m_pNext;
		}
		if( m_pHead )
			m_pHead->m_pPrev=_node;
		_node->m_pNext=m_pHead;
		m_pHead=_node;
		if( m_dwCurCounts==0 )
		{//��ǰΪ������
			m_pTail=m_pVisit=m_pHead;
		}
		m_dwCurCounts++;
		return TRUE;
	}
	BOOL InsertAfter(T* data,DWORD dwPos)
	{
		VCriticalSection myCric(&m_nCriticalSection);
		vListNodePtr<T>* _node=NULL;
		if( (m_dwCurCounts+1)>m_dwMaxCounts )
			return FALSE;
		_node=new vListNodePtr<T>(data);
		if( _node==NULL ) return FALSE;
		if( dwPos<0 ) dwPos=0;
		if( dwPos>=m_dwCurCounts ) dwPos=m_dwCurCounts-1;
		if( m_dwCurCounts==0 )
		{//������
			m_pHead=m_pTail=m_pVisit=_node;
			m_dwCurCounts++;
			return TRUE;
		}
		else
		{
			vListNodePtr<T>* tmp=NULL;
			if( SearchedNode(dwPos,(void**) &tmp) )
			{
				//����λ����Ϣ
				_node->m_dwPos=dwPos+1;
				vListNodePtr<T>* t=tmp->m_pNext;
				while( t )
				{
					t->m_dwPos++;
					t=t->m_pNext;
				}
				t=tmp->m_pNext;
				tmp->m_pNext=_node;
				_node->m_pPrev=tmp;
				_node->m_pNext=t;
				if( t )
					t->m_pPrev=_node;
				else
				{
					m_pTail=_node;
				}
				m_dwCurCounts++;
				return TRUE;
			}
			else
			{
				delete _node;
				::OutputDebugString(TEXT("vListPtr::SearchedNode() Function exist some error!\n"));
				return FALSE;
			}
		}
	}
	BOOL InsertBefore(T* data,DWORD dwPos)
	{
		VCriticalSection myCric(&m_nCriticalSection);
		vListNodePtr<T>* _node=NULL;
		if( (m_dwCurCounts+1)>m_dwMaxCounts )
			return FALSE;
		if( dwPos<0 ) dwPos=0;
		if( dwPos>m_dwCurCounts ) dwPos=m_dwCurCounts;
		_node=new vListNodePtr<T>(data);
		if( _node==NULL ) return FALSE;
		if( m_dwCurCounts==0 )
		{//������
			m_pHead=m_pTail=m_pVisit=_node;
			m_dwCurCounts++;
			return TRUE;
		}
		else
		{
			_node->m_dwPos=dwPos;
			vListNodePtr<T>* tmp=NULL;
			if( SearchedNode(dwPos,(void**) &tmp) )
			{
				//����λ����Ϣ
				vListNodePtr<T>* p=tmp;
				while( p )
				{
					p->m_dwPos--;
					p=p->m_pNext;
				}
				//
				if( tmp->m_pPrev )
				{
					_node->m_pPrev=tmp->m_pPrev;
					tmp->m_pPrev->m_pNext=_node;
					_node->m_pNext=tmp;
					tmp->m_pPrev=_node;
				}
			}
			else
			{//��ӵ�����β
				m_pTail->m_pNext=_node;
				_node->m_pPrev=m_pTail;
				m_pTail=_node;
			}
			m_dwCurCounts++;
			return TRUE;
		}
	}
	void RemoveTail(BOOL bDestroyData=TRUE)
	{
		VCriticalSection myCric(&m_nCriticalSection);
		if( m_dwCurCounts==0 ) return;
		vListNodePtr<T>* _node=m_pTail;
		m_pTail=m_pTail->m_pPrev;
		if( m_pTail ) m_pTail->m_pNext=NULL;
		if( _node==m_pHead ) m_pHead=NULL;
		if( _node==m_pVisit ) m_pVisit=m_pHead;
		if( bDestroyData && _node->m_pData )
		{
			delete _node->m_pData;
			_node->m_pData=NULL;
		}
		delete _node;
		m_dwCurCounts--;
	}
	void RemoveHead(BOOL bDestroyData=TRUE)
	{
		VCriticalSection myCric(&m_nCriticalSection);
		if( m_dwCurCounts==0 ) return;
		vListNodePtr<T>* _node=m_pHead;
		m_pHead=m_pHead->m_pNext;
		if( m_pHead ) m_pHead->m_pPrev=NULL;
		if( _node==m_pTail ) m_pTail=NULL;
		if( _node==m_pVisit ) m_pVisit=m_pHead;
		if( bDestroyData && _node->m_pData )
		{
			delete _node->m_pData;
			_node->m_pData=NULL;
		}
		delete _node;
		m_dwCurCounts--;
		//����λ����Ϣ
		_node=m_pHead;
		while( _node )
		{
			_node->m_dwPos--;
			_node=_node->m_pNext;
		}
	}
	void RemoveAt(DWORD dwPos,BOOL bDestroyData=TRUE)
	{
		VCriticalSection myCric(&m_nCriticalSection);
		vListNodePtr<T>* _node=NULL;
		BOOL bSearched=FALSE;
		if( m_dwCurCounts==0 || dwPos<0 || dwPos>=m_dwCurCounts) return;
		//����Ҫɾ���Ľڵ�
		if( dwPos<=(m_dwCurCounts/2) )
		{//ǰ������
			_node=m_pHead;
			do
			{
				if( _node->m_dwPos==dwPos )
				{
					bSearched=TRUE;
					break;
				}
			}while( (_node=_node->m_pNext)!=NULL );
		}
		else
		{//��������
			_node=m_pTail;
			do
			{
				if( _node->m_dwPos==dwPos )
				{
					bSearched=TRUE;
					break;
				}
			}while( (_node=_node->m_pPrev)!=NULL );
		}
		
		if( bSearched )
		{//��Ѱ��
			T* _data=_node->m_pData;
			if( bDestroyData && _data ){delete _data;_node->m_pData=NULL;}
			//����λ����Ϣ
			vListNodePtr<T>* tmp=_node->m_pNext;
			while( tmp )
			{
				tmp->m_dwPos--;
				tmp=tmp->m_pNext;
			}
			//ɾ���ڵ�
			if( _node==m_pHead )
			{
				m_pHead=m_pHead->m_pNext;
				if( m_pHead )
					m_pHead->m_pPrev=NULL;
				if( _node==m_pTail )
				{//����βָ��
					m_pTail=NULL;
				}
			}
			else if( _node==m_pTail )
			{
				m_pTail=m_pTail->m_pPrev;
				if( m_pTail )
					m_pTail->m_pNext=NULL;
			}
			else
			{
				_node->m_pPrev->m_pNext=_node->m_pNext;
				_node->m_pNext->m_pPrev=_node->m_pPrev;
			}
			if( _node==m_pVisit )
			{//�������ָ��
				m_pVisit=m_pHead;
			}
			delete _node;
			m_dwCurCounts--;
		}
	}
	BOOL GetNext(T** pRet,DWORD* pdwPos=NULL) const
	{
		VCriticalSection myCric(&m_nCriticalSection);

		if( pdwPos ) *pdwPos=-1;
		if( m_pVisit )
		{
			*pRet=m_pVisit->m_pData;
			if( pdwPos ) *pdwPos=m_pVisit->m_dwPos;
			m_pVisit=m_pVisit->m_pNext; 
			return TRUE;
		}
		else
		{
			*pRet=NULL;
			return FALSE;
		}
	}
	BOOL GetPrev(T** pRet,DWORD* pdwPos=NULL) const
	{
		VCriticalSection myCric(&m_nCriticalSection);

		if( pdwPos ) *pdwPos=-1;
		if( m_pVisit )
		{
			*pRet=m_pVisit->m_pData;
			if( pdwPos ) *pdwPos=m_pVisit->m_dwPos;
			m_pVisit=m_pVisit->m_pPrev;
			return TRUE;
		}
		else
		{
			*pRet=NULL;
			return FALSE;
		}
	}
	void MoveToLast() const
	{
		VCriticalSection myCric(&m_nCriticalSection);
		m_pVisit=m_pTail;
	}
	void MoveToFirst() const
	{
		VCriticalSection myCric(&m_nCriticalSection);
		m_pVisit=m_pHead;
	}
	T* GetTail(DWORD* pdwPos=NULL) const
	{
		VCriticalSection myCric(&m_nCriticalSection);
		T* pret=NULL;
		if( pdwPos ) *pdwPos=-1;
		if( m_pTail )
		{
			pret=m_pTail->m_pData;
			if( pdwPos ) *pdwPos=m_pTail->m_dwPos;
		}
		return pret;
	}
	T* GetHead() const
	{
		VCriticalSection myCric(&m_nCriticalSection);
		T* pret=NULL;
		if( m_pHead )
		{
			pret=m_pHead->m_pData;
		}
		return pret;
	}
	T* GetAt(DWORD dwPos) const
	{
		VCriticalSection myCric(&m_nCriticalSection);
		T* pret=NULL;
		vListNodePtr<T>* _node=NULL;
		if( m_dwCurCounts==0 || dwPos<0 || dwPos>=m_dwCurCounts ) return pret;
		if( SearchedNode(dwPos,(void**) &_node) )
		{
			pret=_node->m_pData;
		}
		return pret;
	}
	void Clear()
	{
		VCriticalSection myCric(&m_nCriticalSection);
		vListNodePtr<T>* pTmp=NULL;
		T* _data=NULL;
		while( m_pHead )
		{
			pTmp=m_pHead;
			m_pHead=m_pHead->m_pNext;
			_data=pTmp->m_pData;
			if( _data ){ delete _data;}
			delete pTmp;
		}
		m_pTail=m_pVisit=NULL;
		m_dwCurCounts=0;
	}
	BOOL SetMaxCount(DWORD dwMaxCounts)
	{
		VCriticalSection myCric(&m_nCriticalSection);
		if( dwMaxCounts<0 )
			return FALSE;
		if( dwMaxCounts>V_MAX_LIST_COUNTS_LIMIT )
			m_dwMaxCounts=V_MAX_LIST_COUNTS_LIMIT;
		else if( dwMaxCounts<m_dwCurCounts )
			return FALSE;
		else
			m_dwMaxCounts=dwMaxCounts;
		return TRUE;
	}
	vListPtr<T>& operator=(const vListPtr& src){
		if( this!=&src ){
			Clear();
			m_dwCurCounts=0;
			m_dwMaxCounts=src.m_dwMaxCounts;
			m_pHead=m_pTail=m_pVisit=NULL;
			//
			T* _data=NULL;
			T* dataSrc=NULL;
			src.MoveToFirst();
			while( src.GetNext(&dataSrc) ){
				_data=new T(*dataSrc);
				InsertAfterTail(_data);
			}
		}
		return *this;
	}
	vListPtr(const vListPtr& src){
		m_dwCurCounts=0;
		m_dwMaxCounts=src.m_dwMaxCounts;
		m_pHead=m_pTail=m_pVisit=NULL;
		::InitializeCriticalSection(&m_nCriticalSection);
		//
		T* _data=NULL;
		T* dataSrc=NULL;
		src.MoveToFirst();
		while( src.GetNext(&dataSrc) ){
			_data=new T(*dataSrc);
			InsertAfterTail(_data);
		}
	}
	vListPtr(DWORD dwMaxCounts=V_MAX_LIST_COUNTS_DEFAULT)
	{
		if( dwMaxCounts<0 )
			m_dwMaxCounts=V_MAX_LIST_COUNTS_DEFAULT;
		else if( dwMaxCounts>V_MAX_LIST_COUNTS_LIMIT )
			m_dwMaxCounts=V_MAX_LIST_COUNTS_LIMIT;
		else
			m_dwMaxCounts=dwMaxCounts;
		m_dwCurCounts=0;
		m_pHead=m_pTail=m_pVisit=NULL;
		::InitializeCriticalSection(&m_nCriticalSection);
	}
	~vListPtr()
	{
		Clear();
		::DeleteCriticalSection(&m_nCriticalSection);
	}
private:
	BOOL SearchedNode(DWORD dwPos,void** ppRet) const
	{
		*ppRet=NULL;
		vListNodePtr<T>* _node=NULL;
		BOOL bSearched(FALSE);
		if( dwPos<0 || dwPos>=m_dwCurCounts || m_dwCurCounts==0 ) 
			return bSearched;
		if( dwPos<=(m_dwCurCounts/2) )
		{//ǰ������
			_node=m_pHead;
			while( _node )
			{
				if( _node->m_dwPos==dwPos )
				{
					bSearched=TRUE;
					break;
				}
				_node=_node->m_pNext;
			}
		}
		else
		{//��������
			_node=m_pTail;
			while( _node )
			{
				if( _node->m_dwPos==dwPos )
				{
					bSearched=TRUE;
					break;
				}
				_node=_node->m_pPrev;
			}
		}
		if( bSearched )
		{
			*ppRet=(void*) _node;
			return TRUE;
		}
		return FALSE;
	}

	/////////////////////////////////////////
	vListNodePtr<T>* m_pHead;//ָ��ͷ�ڵ�
	vListNodePtr<T>* m_pTail;//ָ��β�ڵ�
	mutable vListNodePtr<T>* m_pVisit;//���ڷ�������
	mutable CRITICAL_SECTION m_nCriticalSection;//���������ͬ��
	DWORD m_dwCurCounts;//���浱ǰ�����еĽڵ���Ŀ
	DWORD m_dwMaxCounts;//����������洢�����ڵ���
};
/////////////////////////////////////////////////////////////////////
#endif
