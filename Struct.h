#pragma once

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

typedef struct intVector2 {
	int x;
	int y;
}intVector2;

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

typedef struct Vector3{
	float x;
	float y;
	float z;
}Vector3;

typedef struct Matrix3x3
{
	float m[3][3];
} Matrix3x3;

typedef struct Matrix4x4
{
	float m[4][4];
} Matrix4x4;

typedef struct Ball
{

	Vector2 pos;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;
	float radius;
	unsigned int color;

} Ball;

typedef struct Box
{
	Vector2 pos;
	Vector2 size;
	Vector2 valocity;
	Vector2 acceleration;
	float mass;
	unsigned int color;
} Box;