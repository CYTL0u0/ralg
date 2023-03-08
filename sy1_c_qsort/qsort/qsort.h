#ifndef QSORT_H
#define QSORT_H

#include <random>

namespace qs {

	//���ַ���
	struct p_res {
		int left, right, key;
	};

	//����
	void swap(int& a, int& b) {
		int c = a;
		a = b;
		b = c;
	}

	//���ӻ���
	p_res part(int* to_part, int left, int right, bool is_rand = true) {

		//��ֵѡȡ
		int key_index = is_rand ? (rand() % (right - left + 1) + left) : left;
		int key_val = to_part[key_index];
		////��ֵѡȡ(�������ʱ�䲹��)
		//int key_index = rand() % (right - left + 1) + left;
		//key_index = is_rand ? key_index : left;
		//int key_val = to_part[key_index];

		//i:��ǰԪ�أ�p_l:������p_r:�Ҳ�λ��
		int i = left, p_left = left, p_right = right;

		//�������ռ�����ӻ���
		//https://blog.csdn.net/CSMrZ/article/details/81974470
		while (i <= p_right) {
			int cmp = to_part[i];
			if (cmp < key_val)	swap(to_part[i++], to_part[p_left++]);
			else if (cmp > key_val)	swap(to_part[i], to_part[p_right--]);
			else i++;
		}

		return p_res{ p_left,p_right,key_val };
	}

	//ʹ�����ӻ��ֵĿ�������
	int qsort(int* to_sort, int left, int right, bool is_rand = true, int jitter = 0) {

		if (left + jitter < right) {		//����δ���
			p_res part_res = part(to_sort, left, right, is_rand);	//ִ�л���
			qsort(to_sort, left, part_res.left - 1, is_rand);		//�������
			qsort(to_sort, part_res.right + 1, right, is_rand);		//�����Ұ�
			return 0;
		}
		else {
			return 1;	//finished
		}

	}

	//�����
	template <size_t N>
	int qsort(int(&to_sort)[N], bool is_rand = true) {
		return qsort(&to_sort, 0, N - 1, is_rand);
	}

	int bpart(int* a, int l, int r, bool b) {
		int key = b ? a[rand() % (r - l + 1) + l] : a[l];
		while (l < r) {
			while (a[l] < key)l++;
			while (a[r] >= key)r--;
			swap(a[l], a[r]);
		}
		return l;
	}

	int bsort(int* a, int l, int r, bool b) {
		if (l < r) {
			int p = bpart(a, l, r, b);
			bsort(a, l, p - 1, b);
			bsort(a, p + 1, r, b);
			return 0;
		}
		return 1;
	}




}

#endif //!QSORT_H
