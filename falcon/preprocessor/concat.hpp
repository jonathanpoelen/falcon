#ifndef FALCON_PREPROCESSOR_CONCAT_HPP
#define FALCON_PREPROCESSOR_CONCAT_HPP

#define FALCON_CONCAT_I(a,b) a##b
#define FALCON_CONCAT(a,b) FALCON_CONCAT_I(a, b)

#endif
