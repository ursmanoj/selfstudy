static const int size = 100;
static int Q[size];
static int front = -1, rear = -1;

void pushQ(int val) {
	if (front == -1) {
		front=0;
	}
	rear = (rear + 1) % size;
	Q[rear] = val;
}

int pullQ() {
	int ret = Q[front];

	if (front == rear)//last item
		front = rear = -1;
	else
		front = (front + 1) % size;
	return ret;
}

bool isEmptyQ() {
	return (front == -1);
}