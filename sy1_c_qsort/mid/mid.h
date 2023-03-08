#ifndef MID_H
#define MID_H

#include <random>

namespace my {

	//����
	void swap(int& a, int& b) {
		int c = a;
		a = b;
		b = c;
		//std::cout << "swap(" << a << ";" << b <<")\n" ;
	};

	int min(int* a, int l, int r) {
		int p = a[l];
		for (int i = l; i <= r; i++) {

		}
	}

	//���ַ���
	struct p_res {
		int left, right, key;
	};

	//���ӻ���
	p_res part(int* to_part, int left, int right, bool is_rand = true) {

		//��ֵѡȡ���޲�����
		int key_index = is_rand ? (rand() % (right - left + 1) + left) : left;
		//��ֵѡȡ���������������
		//int rval = rand() % (right - left + 1) + left;
		//int key_index = is_rand ? rval : left;

		int key_val = to_part[key_index];

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
			return 1 + 1;	//finished
		}

	}

	//�����
	template <size_t N>
	int qsort(int(&to_sort)[N], bool is_rand = true) {
		return qsort(&to_sort, 0, N - 1, is_rand);
	}

	//ʹ�����ӻ��ֵĴ�������������ָ���±�������ݹ�ʵ��
	int findr(int* to_sort, int left, int right, int pos, bool is_rand = true) {
		p_res part_res = part(to_sort, left, right, is_rand);	//ִ�л���
		if (part_res.left > pos) return findr(to_sort, left, part_res.left - 1, pos, is_rand);	//�������
		else if (right < pos) return findr(to_sort, part_res.right + 1, right, pos, is_rand);	//�����Ҳ�
		else return part_res.key;
	}

	//�ǵݹ�ʵ�ִ�������
	int find(int* to_sort, int left, int right, int pos, bool is_rand = true) {
		while (1) {
			p_res part_res = part(to_sort, left, right, is_rand);			//ִ�л���
			if (part_res.left > pos) right = part_res.left - 1;				//�����
			else if (part_res.right < pos) left = part_res.right + 1;		//�Ҳ�
			else return part_res.key;	//�������У����ص�ǰ��ֵ
		}
	}

	//��ȡ��λ��
	double mid(int* a, int left, int right, bool is_rand = true) {
		int pos = floor(left + right) / 2;
		int l = find(a, left, right, pos, is_rand);
		if ((right - left+1) % 2 == 1) {
			return l;
		}
		else {
			int min = a[pos + 1];
			if (min == l) return l;
			for (int i = pos + 1; i < right; i++) {
				if (a[i] < min) min = a[i];
			}
			return (l + min) / 2;
		}
		
	}

}

#endif // !MID_H

