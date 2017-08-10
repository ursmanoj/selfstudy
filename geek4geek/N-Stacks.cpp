#include <iostream>

using namespace std;

#define ARR_SIZE 10
#define DEFAULT_MAX_STACKS 5


template<class T>
class MultiStack {
private:
	T mArr[ARR_SIZE];
	const int mStackCnt;
	int *mTops;
	int mPrev[ARR_SIZE];
public:
	MultiStack(int stackCnt = DEFAULT_MAX_STACKS) :mStackCnt(stackCnt) {
		mTops = new int[mStackCnt + 1];

		for (int i = 0; i < mStackCnt; i++)
			mTops[i] = -1;

		mTops[mStackCnt] = ARR_SIZE - 1;
		for (int i = 0; i < ARR_SIZE; i++) {
			mPrev[i] = i - 1;
		}
	}

	T top(int stackId, bool &ok) {
		T t; // default value when stack is empty
		if (mTops[stackId] == -1) {
			ok = false;
			return t;
		}

		ok = true;
		return mArr[mTops[stackId]];
	}

	void push(int stackId, T t) {
		// Fetch top from empty stots stack
		int emptySlotId = mTops[mStackCnt];
		mTops[mStackCnt] = mPrev[emptySlotId]; // update top of empty slots stack

											   // Update prev and top of Stack # stackId
		mPrev[emptySlotId] = mTops[stackId];
		mTops[stackId] = emptySlotId;
		mArr[mTops[stackId]] = t; // Push actual info
	}

	void pop(int stackId) {
		int freedSlot = mTops[stackId];
		mTops[stackId] = mPrev[freedSlot];

		// Push freed slot in empty slots stack
		mPrev[freedSlot] = mTops[mStackCnt];
		mTops[mStackCnt] = freedSlot;
	}

	bool empty(int stackId) {
		return mTops[stackId] == -1;
	}
};
