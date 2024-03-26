#pragma once
#include <list>
#include <tuple>
#include <algorithm>



template <typename T, T defaultVal>
class Matrix
{
	struct Node {
		Node(int row, int col, T val) :
			row(row), col(col), val(val) {}

		int row;
		int col;
		T val;
	};

	typename std::list<Node>::iterator getNode(int row, int col) {
		return std::find_if(m_lst.begin(),
							m_lst.end(),
							[row, col] (const Node& node) {
								return node.row == row && node.col == col;
							});
	}

	T getValue(int row, int col) {
		auto it = getNode(row, col);
		return it == m_lst.end() ? defaultVal : (*it).val;
	}

	void setValue(int row, int col, T val) {
		auto it = getNode(row, col);
		
		if (it == m_lst.end()) {
			m_lst.emplace_back(row, col, val);
		} else {
			(*it).val = val;
		}
	}

public:

	class MatrixBracketHelper;

// ---------------------------------------------------------------------------- //
	class NodeProxy
	{
		friend class MatrixBracketHelper;

		NodeProxy(const NodeProxy &) = delete;
		NodeProxy(NodeProxy &&) = delete;
		NodeProxy& operator=(const NodeProxy &) = delete;
		NodeProxy& operator=(NodeProxy &&) = delete;

		NodeProxy(Matrix<T, defaultVal> &matrix, int row, int col) :
			m_matrix(matrix), m_row(row), m_col(col)
		{
			m_val = m_matrix.getValue(m_row, m_col);
		}

	public:
		~NodeProxy() {
			if (isChanged) {
				m_matrix.setValue(m_row, m_col, m_val);
			}
		}

		operator T() {
			return m_val;
		}

		NodeProxy& operator=(const T& val) {
			m_val = val;
			isChanged = true;
			return *this;
		}

	private:
		Matrix<T, defaultVal> &m_matrix;
		int m_row;
		int m_col;
		T m_val;
		bool isChanged = false;
	};
// ---------------------------------------------------------------------------- //


// ---------------------------------------------------------------------------- //
	class MatrixBracketHelper
	{
		friend class Matrix;

		MatrixBracketHelper(const MatrixBracketHelper &) = delete;
		MatrixBracketHelper(MatrixBracketHelper &&) = delete;
		MatrixBracketHelper& operator=(const MatrixBracketHelper &) = delete;
		MatrixBracketHelper& operator=(MatrixBracketHelper &&) = delete;

		MatrixBracketHelper(Matrix<T, defaultVal> &matrix, int row) :
			m_matrix(matrix), m_row(row) {}

	public:
		NodeProxy operator[](int col) {
			return NodeProxy(m_matrix, m_row, col);
		}

	private:
		Matrix<T, defaultVal> &m_matrix;
		int m_row;
	};
// ---------------------------------------------------------------------------- //


// ---------------------------------------------------------------------------- //
	class iterator
	{
		friend class Matrix;
		iterator(typename std::list<Node>::iterator iter) : iter(iter) {}
	public:
		using difference_type		=	int;
		using iterator_category		=	std::forward_iterator_tag;

		iterator() = default;
		iterator(const iterator& t_otherIterator) = default;
		iterator& operator=(const iterator& t_otherIterator) = default;

		iterator& operator++() {
			++iter;
			return *this;
		}
		iterator operator++(int) {
			iterator newIter(*this);
			operator++();
			return newIter;

		}

		bool operator==(const iterator& t_otherIterator) const noexcept {
			return iter == t_otherIterator.iter;
		}
		bool operator!=(const iterator& t_otherIterator) const noexcept {
			return iter != t_otherIterator.iter;
		}

		std::tuple<int, int, T&> operator*() const noexcept {
			Node& node = *iter;
			return std::tie(node.row, node.col, node.val);
		}

		int row() const noexcept {
			return (*iter).row;
		}

		int col() const noexcept {
			return (*iter).col;
		}

		T val() const noexcept {
			return (*iter).val;
		}

	private:
		typename std::list<Node>::iterator iter;
	};
// ---------------------------------------------------------------------------- //


public:
	Matrix() = default;

	size_t size() const noexcept {
		return m_lst.size();
	}

	auto begin() {
		return iterator(m_lst.begin());
	}

	auto end() {
		return iterator(m_lst.end());
	}

	MatrixBracketHelper operator[](int col) {
		return MatrixBracketHelper(*this, col);
	}


private:
	std::list<Node> m_lst;
};

