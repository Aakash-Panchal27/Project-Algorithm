#include <bits/stdc++.h>
using namespace std;

const int MIN_MERGE = 64;
const int MIN_GALLOP = 7;
int cur_minGallop = MIN_GALLOP;

struct run {
	int base_address, len;
	run(){
		base_address = 0;
		len = 0;
	}
	run(int a, int b)
	{
		base_address = a;
		len = b;
	}
};

vector<run> stack_of_runs;
int stackSize;

int compute_minrun(int n)
{
	int r = 0;

	while (n >= 64) {
		r |= n & 1;
		n >>= 1;
	}
	return n + r;
}

void binarysort(vector<int>& data, int start, int lo, int hi)
{
	if (start == lo)
		start++;

	// Iterate from the start index to hi
	for (; start < hi; start++) {
		int ele = data[start];

		// Now find correct position using binary search
		int left = lo, right = start;
		while (left < right) {
			int mid = (left + right) >> 1;
			if (data[mid] > ele)
				right = mid;
			else
				left = mid + 1;
		}

		int n = start - left;

		if (n > 0) {
			int j = start;
			while (j != left) {
				swap(data[j], data[j - 1]);
				j--;
			}
		}

		data[left] = ele;
	}
}

// To reverse a descending sequence
void reverseRange(vector<int>& data, int lo, int hi) {
	while (lo < hi) {
		swap(data[lo++], data[hi--]);
	}
}

// To find the run
int find_Runandmake_Ascending(vector<int>& data, int start, int end)
{
	if (start == end)
		return 0;

	int runHi = start + 1;

	/// Ascending
	if (data[start] < data[runHi])
		while (runHi < end && data[runHi - 1] < data[runHi])
			runHi++;
	///Descending
	else {
		while (runHi < end && data[runHi - 1] > data[runHi])
			runHi++;

		reverseRange(data, start, runHi - 1);
	}

	return runHi - start;
}

inline int binary_search_left(vector<int>& list, int l, int r, int key)
{
	int ans = 0;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (list[mid] < key)
			l = mid + 1;
		else {
			r = mid - 1;
			ans = mid;
		}
	}

	return ans;
}

inline int exponential_search_left(vector<int>& list, int key, int base, int l, int r, bool left)
{
	// Finding range
	int bound = 1;
	while (bound + base < r && list[bound + base] < key)
		bound *= 2;

	if (left)
		return binary_search_left(list, bound / 2 + base, min(bound + 1 + base, r), key);
	else
		return binary_search_left(list, bound / 2 + base, min(bound + 1 + base, r), key);
}

inline int binary_search_right(vector<int>& list, int l, int r, int key)
{
	int ans = 0;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (list[mid] >= key)
		{
			l = mid + 1;
			ans = mid;
		}
		else
			r = mid - 1;
	}

	return ans;
}

inline int exponential_search_right(vector<int>& list, int key, int base, int l, int r, bool left)
{
	// Finding range
	int bound = 1;
	while (bound + base < r && list[bound + base] < key)
		bound *= 2;

	if (left)
		return binary_search_left(list, bound / 2 + base, min(bound + 1 + base, r), key);
	else
		return binary_search_left(list, bound / 2 + base, min(bound + 1 + base, r), key);
}


// Returns k such that a[base + k - 1] < key <= a[base + k]
// If there are elements with equal value then
// leftmost index of equal element.
// @parameter hint--> the starting position of search
int gallopLeft(vector<int>& data, int key, int base, int len, int hint)
{
	// Gallop Right
	if (key > data[base + hint]) {
		int pos = exponential_search_right(data, key, base, base + hint, base + len, true);
		return pos - base;
	}
	// Gallop Left
	else {
		int pos = exponential_search_left(data, key, base, base - hint, base, true);
		return base - pos;
	}
}


// Returns k such that a[base + k - 1] <= key < a[base + k]
// If there are elements with equal value then
// rightmost index of equal element.
// @parameter hint--> the starting position of search
int gallopRight(vector<int>& data, int key, int base, int len, int hint)
{
	// Gallop Right
	if (key >= data[base + hint]) {
		int pos = exponential_search_right(data, key, base, base + hint, base + len, false);
		return pos - base;
	}
	// Gallop Left
	else {
		int pos = exponential_search_left(data, key, base, base - hint, base, false);
		return base - pos;
	}
}


// If len1 <= len2 the mergeLo is called
// First element of run1 must be greater than first element of run2
// and last element of run1 must be greater than all elements of run2
void mergeLo(vector<int>& data, int base1, int len1, int base2, int len2) {
	// Copy smaller run in temporary buffer
	vector<int> small_run(data.begin() + base1, data.begin() + base1 + len1);
	int cursor1 = 0;
	int cursor2 = base2;
	int dest = base1;

	data[dest++] = data[cursor2++];
	if (--len2 == 0) {
		while (cursor1 < len1)
			data[dest++] = small_run[cursor1++];
		return;
	}

	if (len1 == 1) {
		while (cursor2 < len2)
			data[dest++] = data[cursor2++];
		data[dest] = small_run[cursor1];
		return;
	}

	bool done = false;
	int minGallop = cur_minGallop;
	while (true) {
		int count1 = 0; // Number of times in a row that first run won
		int count2 = 0; // Number of times in a row that second run won

		// Straightforward merge procedure until
		// one run starts winning consistently
		do {
			if (data[cursor2] < small_run[cursor1]) {
				data[dest++] = data[cursor2];
				count2++;
				count1 = 0;
				if (--len2 == 0) {
					done = true;
					break;
				}
			}
			else {
				data[dest++] = small_run[cursor1++];
				count1++;
				count2 = 0;
				if (--len1 == 1) {
					done = true;
					break;
				}
			}
		} while (count1 >= minGallop || count2 >= minGallop);

		if (done)
			break;

		// One run is winning consistently then we galloping
		// may lead to a huge win
		do {
			count1 = gallopRight(small_run, data[cursor2], cursor1, len1, 0);
			if (count1 != 0) {
				while (count1--) {
					data[dest++] = small_run[cursor1++];
				}

				len1 -= count1;
				if (len1 <= 1) {
					done = true;
					break;
				}
			}

			data[dest++] = data[cursor2++];
			if (--len2 == 0) {
				done = true;
				break;
			}

			count2 = gallopLeft(data, small_run[cursor1], cursor2, len2, 0);

			if (count2 != 0) {
				while (count2--) {
					data[dest++] = data[cursor1++];
				}

				len2 -= count2;
				if (len2 == 0) {
					done = true;
					break;
				}
			}
			data[dest++] = small_run[cursor1++];
			if (--len1 == 1) {
				done = true;
				break;
			}

			minGallop--;
		} while (count1 >= MIN_GALLOP || count2 >= MIN_GALLOP);

		if (done)
			break;

		// Penalty for coming out from gallop mode
		if (minGallop < 0)
			minGallop = 0;
		minGallop++;

	}

	// Assing the global variable back
	// value should be at least 1
	cur_minGallop = max(1, minGallop);

	// Rest of the things
	if (len1 == 1) {
		while (cursor2 < len2)
			data[dest++] = data[cursor2++];
		data[dest] = small_run[cursor1];
	}
	else {
		while (cursor1 < len1)
			data[dest++] = small_run[cursor1++];
	}

}

// If len2 <= len1 the mergeHi is called
// First element of run1 must be greater than first element of run2
// and last element of run1 must be greater than all elements of run2
void mergeHi(vector<int>& data, int base1, int len1, int base2, int len2) {
	// Copy smaller run in temporary buffer
	vector<int> small_run(data.begin() + base2, data.begin() + base2 + len2);
	int cursor1 = base1 + len1 - 1;
	int cursor2 = len2 - 1;
	int dest = base2 + len2 - 1;

	data[dest--] = data[cursor1--];
	if (--len1 == 0) {
		while (cursor2--)
			data[dest--] = small_run[cursor2--];
		return;
	}

	if (len2 == 1) {
		while (cursor1 >= base1)
			data[dest--] = data[cursor1--];
		data[dest] = small_run[cursor2];
		return;
	}

	bool done = false;
	int minGallop = cur_minGallop;
	while (true) {
		int count1 = 0; // Number of times in a row that first run won
		int count2 = 0; // Number of times in a row that second run won

		// Straightforward merge procedure until
		// one run starts winning consistently
		do {
			if (data[cursor1] < small_run[cursor2]) {
				data[dest--] = data[cursor1--];
				count1++;
				count2 = 0;
				if (--len1 == 0) {
					done = true;
					break;
				}
			}
			else {
				data[dest--] = small_run[cursor2--];
				count2++;
				count1 = 0;
				if (--len2 == 1) {
					done = true;
					break;
				}
			}
		} while (count1 >= minGallop || count2 >= minGallop);

		if (done)
			break;

		// One run is winning consistently then we galloping
		// may lead to a huge win
		do {
			count1 = len1 - gallopRight(data, small_run[cursor2], cursor1, len1, len1 - 1);
			if (count1 != 0) {
				while (count1--) {
					data[dest--] = data[cursor1--];
				}

				len1 -= count1;
				if (len1 == 0) {
					done = true;
					break;
				}
			}

			data[dest--] = small_run[cursor2--];
			if (--len2 == 1) {
				done = true;
				break;
			}

			count2 = len2 - gallopLeft(data, small_run[cursor1], cursor2, len2, 0);

			if (count2 != 0) {
				while (count2--) {
					data[dest--] = small_run[cursor2--];
				}

				len2 -= count2;
				if (len2 <= 1) {
					done = true;
					break;
				}
			}
			data[dest--] = data[cursor1--];
			if (--len1 == 0) {
				done = true;
				break;
			}

			minGallop--;
		} while (count1 >= MIN_GALLOP || count2 >= MIN_GALLOP);

		if (done)
			break;

		// Penalty for coming out from gallop mode
		if (minGallop < 0)
			minGallop = 0;
		minGallop++;

	}

	// Assing the global variable back
	// value should be at least 1
	cur_minGallop = max(1, minGallop);

	// Rest of the things
	if (len2 == 1) {
		while (cursor1 < len2)
			data[dest--] = data[cursor1--];
		data[dest] = small_run[cursor2];
	}
	else {
		while (len2--)
			data[dest--] = small_run[len2];
	}

}


// Merges two runs
// parameter i must be stacksize - 2 or stacksize - 3
void mergeAt(vector<int>& data, int i)
{
	int base1 = stack_of_runs[i].base_address;
	int len1 = stack_of_runs[i].len;
	int base2 = stack_of_runs[i].base_address;
	int len2 = stack_of_runs[i].len;

	stack_of_runs[i].len = len1 + len2;
	if (i == stackSize - 3)
	{
		stack_of_runs[i + 1] = stack_of_runs[i + 2];
	}

	stackSize--;

	// Find position of first element of run2 into run1
	// prior elements of run1 are already in place
	// so just ignore it
	int pos2 = gallopRight(data, data[base2], base1, len1, 0);
	base1 += pos2;
	len1 -= pos2;
	if (len1 == 0)
		return;

	// Find where the last element of run1 goes into run2
	// subsequent elements of run2 are already in place
	// so just ignore it
	int pos1 = gallopLeft(data, data[base1], base2, len2, len2 - 1);
	if (pos1 == 0)
		return;

	if (len1 <= len2)
		mergeLo(data, base1, len1, base2, len2);
	else
		mergeHi(data, base1, len1, base2, len2);

}

// This method is called each time a new run is pushed onto the stack,
void mergecollapse(vector<int>& data) {
	while (stackSize > 1) {
		int n = (int) stackSize - 2;
		if (n > 0 && stack_of_runs[n - 1].len <= stack_of_runs[n].len + stack_of_runs[n + 1].len) {
			if (stack_of_runs[n - 1].len < stack_of_runs[n + 1].len)
				n--;
			mergeAt(data, n);
		}
		else if (stack_of_runs[n].len <= stack_of_runs[n - 1].len) {
			mergeAt(data, n);
		}
		else {
			break;
		}
	}
}

// Merges all runs on the stack until only one remains.  This method is
// called once, to complete the sort at last.
void mergeForceCollapse(vector<int>& data)
{
	while (stackSize > 1) {
		int n = (int) stackSize - 2;
		if (n > 0 && stack_of_runs[n - 1].len < stack_of_runs[n - 2].len)
				n--;
		mergeAt(data, n);
	}
}


void Timsort(vector<int>& data)
{
	int low = 0, high = data.size();
	int remaining = data.size();

	if (remaining < MIN_MERGE)
	{
		int runlen = find_Runandmake_Ascending(data, low, high);
		binarysort(data, runlen, low, high);
		return;
	}

	int minRun = compute_minrun(remaining);

	do {
		int runlen = find_Runandmake_Ascending(data, low, high);

		if (runlen < minRun) {
			int force_len = remaining <= minRun ? remaining : minRun;
			binarysort(data, low + runlen, low, high);
			runlen = force_len;
		}

		stack_of_runs[stackSize++].base_address = low;
		stack_of_runs[stackSize++].len = runlen;

		mergecollapse(data);

		low += runlen;
		remaining -= runlen;

	} while (remaining != 0);

	mergeForceCollapse(data);
}


int main()
{
	srand(unsigned(time(0)));

	vector<int> data;

	for (int i = 0; i < 1000; i++)
		data.push_back(rand());

    for(auto i:data)
        cout << i << " ";
    cout << endl << endl << endl;

	int size = data.size();

	// standard procedure to find max. stack size for given n
	int stack_max_size = size < 120 ? 5 : size < 1542 ? 10 : size < 119151 ? 19 : 40;

	stack_of_runs.resize(stack_max_size);
	for (int i = 0; i < stack_max_size; i++) {
		stack_of_runs[i] = run();
	}

	stackSize = 0;

	Timsort(data);

	for(auto i:data)
        cout << i << " ";

	return 0;
}
