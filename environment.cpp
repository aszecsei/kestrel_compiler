#include "environment.h"
#include "log.h"
#include <string>
#include "lexical.h"
#include <iostream>
#include "symboltable.h"

Environment* Environment::s_Head = NULL;
int Environment::s_blkLevel = 0;

Environment::Environment() {
	if (NULL == s_Head)
		s_Head = this;
	m_blkLevel = s_blkLevel;
	m_nextEvn = NULL;
}

void Environment::EnterBlk() {
	s_blkLevel ++;
}

void Environment::LeaveBlk() {
	s_blkLevel --;
	// remove the nested block environment since it is no longer accessible
	for (Environment *e = s_Head; e != NULL; e = e->m_nextEvn) {
		bool nested = (e->m_blkLevel > s_blkLevel);
		if (nested) {
			e->Out();
		}
	}
}

void Environment::Out() {
	Environment **p = &s_Head;
	for (; (*p) != NULL
		; p = &((*p)->m_nextEvn)) {
		if ((*p) == this) {
			//need to be remove
			*p = (*p)->m_nextEvn;
			delete this;
			break;
        }
    }
}

Attribute * Environment::lookup( uint32_t identifier, attribute_type t ) {
	if( this==NULL || attr == NULL) {
		std::string attrtype;
		switch (t){
			case ATTR_BLOCK:
				attrtype = "Block";
				break;
			case ATTR_CONST:
				attrtype = "Constant";
				break;			
			case ATTR_FINAL:
				attrtype = "Final";
				break;		
			case ATTR_TYPE:
				attrtype = "Type";
				break;			
			case ATTR_EXCEPT:
				attrtype = "Exception";
				break;			
			case ATTR_VAR:
				attrtype = "Variable";
				break;			
			case ATTR_PROC:
				attrtype = "Procedure";
				break;			
			case ATTR_FUNC:
				attrtype = "Function";
				break;
		}

		Log::Error(ER_UNDEF_REF, get_lex_this().line, get_lex_this().char_index, lex_get(get_lex_this()), attrtype);

		return NULL;
	} else if( identifier == attr->identifier && t == attr->type ) {
		return attr;
	} else {
		return m_nextEvn->lookup(identifier, t);
	}
}
//method to see if the attr-type is in the given set32_t
Attribute * Environment::lookup( uint32_t identifier,  set32_t types) {
    if(this != NULL) {
        printf("Looking for ");
        lex_put(get_lex_this(), stdout);
        printf(" in environment: ");
        this->print();
    }
    
	if( this==NULL || attr == NULL) {
		std::string attrtype = "=BUG=";

		Log::Error(ER_UNDEF_REF, get_lex_this().line, get_lex_this().char_index, lex_get(get_lex_this()), attrtype);
		return NULL;
	}else if( identifier == attr->identifier && in_set32(attr->type, types) ) {
		return attr;
	} else {
		return m_nextEvn->lookup(identifier, types);
	}
}


Environment * Environment::add( uint32_t identifier, Attribute * a, attribute_type t, access_level ac ) {
	Environment * result = new Environment();
	result->attr = new Attribute();
	result->attr->attr = a;
	result->attr->identifier = identifier;
        result->attr->type = t;
        result->attr->access = ac;
	result->m_nextEvn = this;
	s_Head = result;
	return result;
}

void Environment::print() {
    Environment * currEnv = this;
    std::cout << "[";
    while(currEnv != NULL) {
        std::cout << " ";
        symbol_put( (symbol_handle) currEnv->attr->identifier, stdout );
        if(currEnv->m_nextEvn != NULL)
            std::cout << ",";
        else
            std::cout << " ]\n";
        currEnv = currEnv->m_nextEvn;
    }
}

// =BUG= Set properties in the constructor
