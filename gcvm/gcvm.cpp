#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 256
#define IGCT 8

typedef enum
{
	INT,
	TWIN
} ObjectType;

typedef struct sObject
{
	ObjectType type;
	unsigned char marked; 

	struct sObject* next;

	union
	{
		int value;

		struct
		{
			struct sObject* head;
			struct sObject* tail;
		};
	};
} Object;


typedef struct
{
	Object* stack[STACK_MAX_SIZE];
	int stackSize;

	Object* firstObject;

	int numObjects;
	int maxObjects;
} VM;

void push(VM* vm, Object* value)
{
	vm->stack[vm->stackSize++] = value;
}

Object* pop(VM* vm)
{
	return vm->stack[--vm->stackSize];
}

VM* newVM()
{
	VM* vm = (VM*)malloc(sizeof(VM));
	vm->stackSize = 0;
	vm->firstObject = NULL;

	vm->numObjects = 0;
	vm->maxObjects = IGCT;

	return vm;
}

Object* newObject(VM* vm, ObjectType type) 
{
	Object* object = (Object*)malloc(sizeof(Object));
	object->type = type;
	object->marked = 0;

	object->next = vm->firstObject;
	vm->firstObject = object;

	vm->numObjects++;

	return object;
}

void pushInt(VM* vm, int intValue)
{
	Object* object = newObject(vm, INT);
	object->value = intValue;
	push(vm, object);
}

Object* pushTwin(VM* vm)
{
	Object* object = newObject(vm, TWIN);
	object->tail = pop(vm);
	object->head = pop(vm);

	push(vm, object);

	return object;
}

void markAll(VM *vm)
{
	for (int i = 0; i < vm->stackSize; i++)
	{
		mark(vm->stack[i]);
	}
}

void mark(Object *object)
{
	if (object->marked) return;

	object->marked = 1;

	if (object->type == TWIN)
	{
		mark(object->head);
		mark(object->tail);
	}
}

void markSweep(VM* vm)
{
	Object** object = &vm->firstObject;

}

int main(int argc, const char** argv) 
{
	return (0);
}
