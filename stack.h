#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {

private:
    T* stack_;
    unsigned int max_size_;
    unsigned int top_;

public:

    /**
     * @brief Costruttore di default
    */
    Stack() : stack_(nullptr), max_size_(0), top_(0) {}

    /**
     * @brief Costruttore di default che inizializza lo stack con la dimensione massima specificata
     * 
     * @param max_size massima dimensione dello stack
     * 
     * @throw std::bad_alloc se non è possibile allocare lo spazio necessario per lo stack
    */
    Stack(unsigned int max_size) : max_size_(max_size), top_(0) {
        try {
            stack_ = new T[max_size_];
        } catch (std::bad_alloc& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            stack_ = nullptr;
            throw;
        }
    }
    
    /**
     * @brief Costruttore che inizializza lo stack con i valori specificati
     * 
     * @param first iteratore all'inizio della sequenza di valori da inserire nello stack
     * @param last iteratore alla fine della sequenza di valori da inserire nello stack
     * 
     * @throw std::bad_alloc se non è possibile allocare lo spazio necessario per lo stack
     */ 
    template <typename Iter>
    Stack(Iter first, Iter last) : max_size_(last - first), top_(0) {
        try {
            stack_ = new T[max_size_];
            for (; first != last && top_ < max_size_; ++first) {
                stack_[top_++] = static_cast<T>(*first);
            }
        } catch (std::bad_alloc& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            stack_ = nullptr;
            throw;
        }
    }

    /**
     * @brief Costruttore di copia
     * 
     * @param other stack da copiare
    */
    Stack(const Stack& other) : max_size_(other.max_size_), top_(other.top_) {
        try {
            stack_ = new T[max_size_];
            for (unsigned int i = 0; i < top_; ++i) {
                stack_[i] = other.stack_[i];
            }
        } catch (std::bad_alloc& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            stack_ = nullptr;
            throw;
        }
    }

    /**
     * @brief Distruttore
    */
    ~Stack() {
        delete[] stack_;
        stack_ = nullptr;
    }

    /**
     * @brief Operatore di assegnazione
     * 
     * @param other stack da copiare
     * 
     * @return Stack& riferimento allo stack copiato
    */
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            Stack tmp(other, other.max_size_, other.top_);
            std::swap(stack_, tmp.stack_);
            std::swap(max_size_, tmp.max_size_);
            std::swap(top_, tmp.top_);
        }
        return *this;
    }

    /**
     * @brief Operatore di confronto
     * 
     * @param other stack da confrontare
     * 
     * @return true se gli stack sono uguali
    */
    bool operator==(const Stack& other) const {
        if (max_size_ != other.max_size_ || top_ != other.top_) {
            return false;
        }
        for (unsigned int i = 0; i < top_; ++i) {
            if (stack_[i] != other.stack_[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Metodo per inserire un elemento in cima allo stack
     * 
     * @param value valore da inserire
     * 
     * @throw std::length_error se lo stack è pieno e si prova ad inserire un elemento
    */
    void push(const T& value) {
        if (top_ < max_size_) {
            stack_[top_++] = value;
        }
        else {
            throw std::length_error("Stack overflow in push (top > max_size)");
        }
    }

    /**
     * @brief Metodo per rimuovere un elemento in cima allo stack e restituirlo
     * 
     * @throw std::length_error se lo stack è vuoto e si prova a rimuovere un elemento
     * 
     * @return T& riferimento all'elemento rimosso
    */
    T& pop() {
        if (top_ > 0)
            return stack_[--top_];
        else
            throw std::length_error("Stack underflow in pop (top < 0)");
    }

    /**
     * @brief Metodo per ottenere l'elemento in cima allo stack
     * 
     * @return T& riferimento all'elemento in cima allo stack
    */
    T& top() const {
        if (top_ > 0)
            return stack_[top_ - 1];
        else
            throw std::length_error("Stack underflow in top (top < 0)");
    }

    /**
     * @brief Metodo per cancellare tutti gli elementi dello stack (logicamente)
     * 
    */
    void clear() {
        top_ = 0;
    }

    /**
     * @brief Metodo per verificare se lo stack è vuoto
     * 
     * @return true se lo stack è vuoto
    */
    bool empty() const {
        return top_ == 0;
    }

    /**
     * @brief Metodo per verificare se lo stack è pieno
     * 
     * @return true se lo stack è pieno
    */
    bool full() const {
        return top_ == max_size_;
    }

    /**
     * @brief Metodo per ottenere la dimensione dello stack (elemento in cima)
     * 
     * @return unsigned int dimensione dello stack (top)
    */
    unsigned int size() const {
        return top_;
    }

        /**
     * @brief Metodo per ottenere la dimensione massima dello stack
     * 
     * @return unsigned int dimensione massima dello stack
    */
    unsigned int max_size() const {
        return max_size_;
    }

    /**
     * @brief Metodo per stampare lo stack (da fondo a cima - sinistra a destra)
     * 
     * @param os stream di output
     * @param s stack da stampare
     * 
     * @return std::ostream& stream di output
    */
    friend std::ostream& operator<<(std::ostream &os, const Stack &s) {  
        os << "[ ";
        if (s.empty()) {
            os << "stack empty ";
        }
        else {
            for (unsigned int i = 0; i < s.top_; i++) {
                os << s.stack_[i] << " ";
            }
        }
        os << "]" << std::endl;
        return os;
    }

    /**
     * @brief Metodo pubblico per riempire lo stack con una nuova sequenza di elementi (sovrascrizione permessa)
     * 
     * @param first iteratore all'inizio della sequenza
     * @param last iteratore alla fine della sequenza
     * 
     * @throw std::length_error se la sequenza di elementi è più lunga di quella dello stack
    */
    template <typename Iter>
    void fill(Iter first, Iter last) {
        try {
            if ((last - first) > max_size_)
                throw std::length_error("Errore fill(): la sequenza di elementi è più lunga di quella dello stack");
            
            clear();
            
            for (; first != last && top_ < max_size_; ++first) {
                stack_[top_++] = static_cast<T>(*first);
            }
        } catch (std::bad_alloc& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            throw;
        }
    }

    /**
     * @brief metodo pubblico che, dato un predicato generico P su un 
     * elemento di tipo T (liberamente definibile dall'utente), ritorna vero se
     * l’elemento soddisfa il predicato P.
     * 
     * @param predicate predicato generico
     * 
     * @return true se l'elemento soddisfa il predicato P
     * @return false se l'elemento non soddisfa il predicato P
    */
    template <typename P>
    bool checkif(const P& predicate, const T &element) const {
        if (predicate(element)) {
            return true;
        }
        return false;
    }    

// ---------------------- ITERATORI ----------------------

    // // Solo se serve anche const_iterator aggiungere la seguente riga
	class const_iterator; // forward declaration

    /**
     * @brief Classe per l'iteratore dello stack (forward iterator)
    */
	class iterator {

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef T*                        pointer;
		typedef T&                        reference;

	
		iterator() : stack_(nullptr), top_(0) {}
		
		iterator(const iterator &other) : stack_(other.stack_), top_(other.top_) {}

		iterator& operator=(const iterator &other) {
            if (this != &other) {
                stack_ = other.stack_;
                top_ = other.top_;
            }
            return *this;
        }

		~iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
            return *stack_;
		}
        
		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
            return &stack_;
		}

		// Operatore di iterazione post-incremento
		iterator operator++(int) {
            iterator tmp(stack_, top_);
            stack_ = stack_ + 1;
            return tmp;
		}

		// Operatore di iterazione pre-incremento
		iterator& operator++() {
            stack_ = stack_ + 1;
            return *this;
		}

		// Uguaglianza
		bool operator==(const iterator &other) const {
            return (stack_ == other.stack_);
		}

		// Diversita'
		bool operator!=(const iterator &other) const {
            return (stack_ != other.stack_);
		}
		
		// Solo se serve anche const_iterator aggiungere le seguenti definizioni
		friend class const_iterator;

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
            return (stack_ == other.stack_);
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
            return (stack_ != other.stack_);
		}

		// Solo se serve anche const_iterator aggiungere le precedenti definizioni

	private:

		friend class Stack;

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		iterator(T *s, unsigned int t) : stack_(s), top_(t) {}

        T *stack_;

        unsigned int top_;
		
	}; // fine classe iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	iterator begin() {
		return iterator(stack_, 0);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	iterator end() {
		return iterator(stack_ + top_, top_);
	}
	
	
	class const_iterator {

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		const_iterator() : stack_(nullptr), top_(0) {}
		
		const_iterator(const const_iterator &other) : stack_(other.stack_), top_(other.top_) {}

		const_iterator& operator=(const const_iterator &other) {
            if (this != &other) {
                stack_ = other.stack_;
                top_ = other.top_;
            }
            return *this;
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
            return *stack_;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
            return &stack_;
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
            const_iterator tmp(*this, top_);
            stack_ = stack_ + 1;
            return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
            stack_ = stack_ + 1;
            return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
            return (stack_ == other.stack_);
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
            return (stack_ != other.stack_);
		}

		// Solo se serve anche iterator aggiungere le seguenti definizioni
		
		friend class iterator;

		// Uguaglianza
		bool operator==(const iterator &other) const {
			return (stack_ == other.stack_);
		}

		// Diversita'
		bool operator!=(const iterator &other) const {
			return (stack_ != other.stack_);
		}

		// Costruttore di conversione iterator -> const_iterator
		const_iterator(const iterator &other) : stack_(other.stack_), top_(other.top_) {}

		// Assegnamento di un iterator ad un const_iterator
		const_iterator &operator=(const iterator &other) {
            if (this != &other) {
                stack_ = other.stack_;
                top_ = other.top_;
            }
            return *this;
		}

		// Solo se serve anche iterator aggiungere le precedenti definizioni

	private:

		friend class Stack;

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const T *s, unsigned int t) : stack_(s), top_(t) {}

        const T *stack_;

        unsigned int top_;
		
	}; // fine classe const_iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(stack_, 0);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(stack_ + top_, top_);
	}

// ---------------------- FINE ITERATORI ----------------------

// ---------------------- INIZIO ITERATORE CUSTOM ----------------------

    /**
     * @brief Classe Iteratore Custom di sola lettura per lo stack (forward iterator)
    */
    class readOnlyIterator {

    public:

        readOnlyIterator() : stack_(nullptr), top_(0) {}

        readOnlyIterator(const readOnlyIterator &other) : stack_(other.stack_), top_(other.top_) {}

        T& operator*() const {
            // return stack_[top_];
            return *stack_;
        }

        T* operator->() const {
            // return &stack_[top_];
            return &stack_;
        }

        readOnlyIterator& operator++() {
            // --top_;
            stack_ = stack_ - 1;
            return *this;
        }

        readOnlyIterator operator++(int) {
            readOnlyIterator tmp(stack_, top_);
            operator++();
            return tmp;
        }

        bool operator==(const readOnlyIterator& other) const {
            // return stack_ == other.stack_ && top_ == other.top_;
            return stack_ == other.stack_;
        }
        
        bool operator!=(const readOnlyIterator& other) const {
            // return stack_ != other.stack_ || top_ != other.top_;
            return stack_ != other.stack_;
        }

    private:

        friend class Stack;

        readOnlyIterator(T *s, unsigned int t) : stack_(s), top_(t) {}

        T* stack_;

        unsigned int top_;

    };

    readOnlyIterator readOnlyBegin() const {
        return readOnlyIterator(stack_ + top_ - 1, top_ - 1);
    }

    readOnlyIterator readOnlyEnd() const {
        return readOnlyIterator(stack_ - 1, 0);
    }

// ---------------------- FINE ITERATORE CUSTOM ----------------------

};

#endif