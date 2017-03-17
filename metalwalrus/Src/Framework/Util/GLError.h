#ifndef GLERROR_H
#define GLERROR_H
#pragma once

void _check_gl_error(const char *file, int line);

#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

#endif