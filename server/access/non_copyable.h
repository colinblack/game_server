#ifndef CPPSOCKET_NONCOPYABLE_H_
#define CPPSOCKET_NONCOPYABLE_H_

/*! \brief ����Ҫ�󲻿ɸ�ֵ(��������)���඼���Լ̳��ڴ�
 *  \note ժ��IceUtil::::noncopyable
 */

  class NonCopyable
  {

  protected:
      NonCopyable() {}
      ~NonCopyable() {}

  private:
      NonCopyable(const NonCopyable &);
      const NonCopyable & operator=(const NonCopyable &);
  };


#endif // AC_NONCOPYABLE_H_
