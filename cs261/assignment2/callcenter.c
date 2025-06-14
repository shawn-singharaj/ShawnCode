// EC 
// Shawn Singharaj

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"


struct call {
	int id;
	char name[30];
	char reason[100];
};

int output_menu(){
	int user_input;
	do{
		printf("\n1. Receive a new call\n2. Answer a call\n3. Current State of stack - answered calls\n");
		printf("4. Current state of queue - calls to be answered\n5. Quit\nChoose an option: ");
		scanf("%d", &user_input);

		if(user_input < 1 || user_input > 5){
			printf("\nInvalid input, try again.");
		}
	}while(user_input < 1 && user_input > 5);
	return user_input;
}

void receive_call(struct queue* call_queue, int id){
	struct call* caller = malloc(sizeof(struct call));
	printf("Enter caller's name: ");
	scanf("%s", caller->name);
	printf("Enter reason for calling: ");
	scanf("%s", caller->reason);
	caller->id = id;

	queue_enqueue(call_queue, caller);
	printf("\nThe call has been successully added to the queue!");
}

void answer_call(struct queue* call_queue, struct stack* call_stack){
	if(queue_isempty(call_queue)){
		printf("No more calls to be answered!\n");
		return;
	}
	struct call* answered_call = queue_dequeue(call_queue);
	printf("The following call has been answered and added to the stack!\n");
	printf("Caller ID: %d\nCaller name: %s\nCall reason: %s", answered_call->id, answered_call->name, answered_call->reason);
	stack_push(call_stack, answered_call);
}

void display_stack(struct stack* call_stack, int num_answered){
	printf("There have been %d calls answered.", num_answered);
	struct call* head_stack = stack_top(call_stack);
	printf("\nLatest call answered: Caller ID: %d\nCaller name: %s\nCall reason: %s", head_stack->id, head_stack->name, head_stack->reason);
}

void display_queue(struct queue* call_queue, int num_unanswered){
	printf("There are %d calls to be answered.", num_unanswered);
	struct call* head_queue = queue_front(call_queue);
	printf("\nLatest call answered: Caller ID: %d\nCaller name: %s\nCall reason: %s", head_queue->id, head_queue->name, head_queue->reason);
}

void free_stack(struct stack* call_stack) {
    while (!stack_isempty(call_stack)) {
        struct call* answered_call = stack_pop(call_stack);
        free(answered_call);  
    }
	free(stack_list(call_stack));
    free(call_stack);
}

void free_queue(struct queue* call_queue) {
    while (!queue_isempty(call_queue)) {
        struct call* unanswered_call = queue_dequeue(call_queue);
        free(unanswered_call);  
    }
	free(queue_array(call_queue));
	queue_free(call_queue);
}

int main(int argc, char const *argv[]) {
	int id = 0, num_answered = 0, num_unanswered = 0;
	struct queue* call_queue = queue_create();
	struct stack* call_stack = stack_create();

	int user_input;
	do{
		user_input = output_menu();
		switch(user_input){
			case 1:
				id++;
				num_unanswered++;
				receive_call(call_queue, id);
				break;
			case 2:
				num_answered++;
				num_unanswered--;
				answer_call(call_queue, call_stack);
				break;
			case 3:
				display_stack(call_stack, num_answered);
				break;
			case 4:
				display_queue(call_queue, num_unanswered);
				break;
		}
	}while(user_input != 5);

	free_stack(call_stack);
	free_queue(call_queue);

	return 0;
}
