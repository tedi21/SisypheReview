#ifndef _COPY_PTR_H_
#define _COPY_PTR_H_

#include <boost/shared_ptr.hpp>
#include <vector>

template <class T>
inline
boost::shared_ptr<T> copy_ptr(boost::shared_ptr<T> p)
{
	return boost::shared_ptr<T> (p ? new T(*p) : 0);
}

template <class T>
inline
std::vector< boost::shared_ptr<T> > copy_ptr(const std::vector< boost::shared_ptr<T> >& v)
{
    std::vector< boost::shared_ptr<T> > r(v.size());
    std::transform(
		v.begin(), v.end(), 
		r.begin(), 
		static_cast<boost::shared_ptr<T>(*)(boost::shared_ptr<T>)>(copy_ptr));
	return r;
}


#endif // _COPY_PTR_H_