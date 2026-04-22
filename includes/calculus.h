#ifndef CALCULUS_H
#define CALCULUS_H

#define ROTRIGHT32(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define ROTLEFT32(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#endif