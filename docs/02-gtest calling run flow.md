# 概述
>   本文主要通过示例代码，描述gtest调用的过程

# 测试代码结构
1.代码包含结构
- Environment
- TestFixture1(Test: NoName, Test: WithName)
- TestFixture2(Test: NoName)
- TEST

2.操作打印结果(entered.../leaving...)
``` console print
Running main() from gmock_main.cc
Environment construct entered...                                
[==========] Running 4 tests from 3 test cases.
[----------] Global test environment set-up.                    
Environment SetUp entered...                                    0-- Run Environment SetUp
[----------] 1 test from TestNoFixture
[ RUN      ] TestNoFixture.NoName
TEST TestNoFixture
[       OK ] TestNoFixture.NoName (0 ms)
[----------] 1 test from TestNoFixture (0 ms total)

[----------] 2 tests from TestFixture1
TestFixture1 SetUpTestCase entered...                           1-- Run TestFixture1 SetUpTestCase
[ RUN      ] TestFixture1.NoName
TestFixture1 construct entered...                               2-- Run TestFixture1 constract
TestFixture1 SetUp entered...                                   3-- Run TestFixture1 SetUp
TEST TestFixture1 NoName
TestFixture1 TearDown leaving...                                3-- End TestFixture1 TearDown
TestFixture1 destruct leaving...                                2-- End TestFixture1 destract
[       OK ] TestFixture1.NoName (0 ms)
[ RUN      ] TestFixture1.WithName
TestFixture1 construct entered...                               2-- Run TestFixture1 constract
TestFixture1 SetUp entered...                                   3-- Run TestFixture1 SetUp
TEST TestFixture1 WithName
TestFixture1 TearDown leaving...                                3-- End TestFixture1 TearDown
TestFixture1 destruct leaving...                                2-- End TestFixture1 destract
[       OK ] TestFixture1.WithName (16 ms)
TestFixture1 TearDownTestCase leaving...                        1-- End TestFixture1 TearDownTestCase
[----------] 2 tests from TestFixture1 (16 ms total)

[----------] 1 test from TestFixture2
TestFixture2 SetUpTestCase entered...                           1-- Run TestFixture2 SetUpTestCase
[ RUN      ] TestFixture2.NoName
TestFixture2 construct entered...                               2-- Run TestFixture2 constract
TestFixture2 SetUp entered...                                   3-- Run TestFixture2 SetUp
TEST TestFixture2
TestFixture2 TearDown leaving...                                3-- End TestFixture2 TearDown
TestFixture2 destruct leaving...                                2-- End TestFixture2 destract
[       OK ] TestFixture2.NoName (0 ms)
TestFixture2 TearDownTestCase leaving...                        1-- End TestFixture2 TearDownTestCase
[----------] 1 test from TestFixture2 (0 ms total)

[----------] Global test environment tear-down                  
Environment TearDown leaving...                                 0-- Run Environment TearDowm
[==========] 4 tests from 3 test cases ran. (32 ms total)
[  PASSED  ] 4 tests.
Environment destruct leaving...
Press any key to continue . . .
```

3.分析调用顺序
``` Run flow order
Environments SetUp Entered...
    Test TEST(Differ from TEST_F)
    SetUpTestCase1 Entered...
        TestFixture1 constract Entered...
            SetUp Entered...
                Test NoName
            TearDown Ended...
        TestFixture1 destruct Ended...
        TestFixture1 constract Entered...
            SetUp Entered...
                Test WithName
            TearDown Ended...
        TestFixture1 destruct Ended...
    SetUpTestCase1 Ended...
    SetUpTestCase2 Entered...
        TestFixture2 constract Entered...
            SetUp Entered...
                Test NoName
            TearDown Ended...
        TestFixture2 destruct Ended...
    SetUpTestCase2 Ended...
Environments TearDown Ended...
```

# 源码分析
## RUN_ALL_TESTS
``` C++
inline int RUN_ALL_TESTS() {
    return ::testing::UnitTest::GetInstance()->Run();
}
```
gtest执行的入口为RUN_ALL_TESTS，其内部调用了Run()方法

## UnitTest.Run
``` C++
return internal::HandleExceptionsInMethodIfSupported(
    impl(),
    &internal::UnitTestImpl::RunAllTests,
    "auxiliary test code (environments or event listeners)") ? 0 : 1;
```
Run方法最终会调用RunAllTests方法

## RunAllTests
``` C++
// Runs each test case if there is at least one test to run.
if (has_tests_to_run) {
    // Sets up all environments beforehand.
    repeater->OnEnvironmentsSetUpStart(*parent_);
    ForEach(environments_, SetUpEnvironment);
    repeater->OnEnvironmentsSetUpEnd(*parent_);

    // Runs the tests only if there was no fatal failure during global set-up.
    if (!Test::HasFatalFailure()) {
        for (int test_index = 0; test_index < total_test_case_count();
            test_index++) {
          GetMutableTestCase(test_index)->Run();
        }
    }

    // Tears down all environments in reverse order afterwards.
    repeater->OnEnvironmentsTearDownStart(*parent_);
    std::for_each(environments_.rbegin(), environments_.rend(),
                TearDownEnvironment);
    repeater->OnEnvironmentsTearDownEnd(*parent_);
}
```
- 以上的代码之前会先处理FLAG、Listener等内容
- 之后可发现遍历Environment列表，执行SetUp方法(line 5)
- 然后for循环中顺序执行所有的测试用例(line 10-13)
- 最后遍历Environment列表，执行TearDown方法(line 18-19)
SetUpEnvironment/TearDownEnvironment调用了Environment对象的SetUp和TearDown方法:
``` C++
// Helpers for setting up / tearing down the given environment.  They
// are for use in the ForEach() function.
static void SetUpEnvironment(Environment* env) { env->SetUp(); }
static void TearDownEnvironment(Environment* env) { env->TearDown(); 
```

## TestCase.Run
``` C++
internal::HandleExceptionsInMethodIfSupported(
    this, &TestCase::RunSetUpTestCase, "SetUpTestCase()");

    const internal::TimeInMillis start = internal::GetTimeInMillis();
    for (int i = 0; i < total_test_count(); i++) {
        GetMutableTestInfo(i)->Run();
    }
    elapsed_time_ = internal::GetTimeInMillis() - start;

    impl->os_stack_trace_getter()->UponLeavingGTest();
    internal::HandleExceptionsInMethodIfSupported(
      this, &TestCase::RunTearDownTestCase, "TearDownTestCase()");
```
- 执行TestCase的SetUpTestCase方法(line 1-2)
- 根据该TestCase下Test的数量，单独执行每个Test(line 5-7)
- 执行TestCase的TearDownTestCase方法(line 11-12)

## TestInfo.Run
```
// Creates the test object.
Test* const test = internal::HandleExceptionsInMethodIfSupported(
    factory_, &internal::TestFactoryBase::CreateTest,
    "the test fixture's constructor");

// Runs the test only if the test object was created and its
// constructor didn't generate a fatal failure.
if ((test != NULL) && !Test::HasFatalFailure()) {
    // This doesn't throw as all user code that can throw are wrapped into
    // exception handling code.
    test->Run();
}

// Deletes the test object.
impl->os_stack_trace_getter()->UponLeavingGTest();
internal::HandleExceptionsInMethodIfSupported(
    test, &Test::DeleteSelf_, "the test fixture's destructor");
```
- 在执行每个测试实例的时候，才单独去构建测试实例的对象(line 2-4)
- 然后再去执行每个Test的具体内容(line 11)
- 最后释放该Test的测试实例(line 16-17)

## Test.Run
```
internal::HandleExceptionsInMethodIfSupported(this, &Test::SetUp, "SetUp()");

// We will run the test only if SetUp() was successful.
if (!HasFatalFailure()) {
    impl->os_stack_trace_getter()->UponLeavingGTest();
    internal::HandleExceptionsInMethodIfSupported(
        this, &Test::TestBody, "the test body");
}

// However, we want to clean up as much as possible.  Hence we will
// always call TearDown(), even if SetUp() or the test body has
// failed.
impl->os_stack_trace_getter()->UponLeavingGTest();
internal::HandleExceptionsInMethodIfSupported(
    this, &Test::TearDown, "TearDown()");
```
- 执行Test实例的SetUp方法(line 1)
- 执行Test实例的具体内容(TEST_F)中的内容(lien 6-7)
- 执行Test实例的TearDown方法(line 14-15)

# 结论
## 执行过程
- 预处理FLAG等
- 构建所有Environment对象，放入全局环境列表，遍历执行SetUp
    + 遍历测试用例，单独执行静态方法SetUpTestCase
        * 顺序为每个Test创建测试实例(constract)
            - 执行测试实例的SetUp
                + 执行TEST_F中的测试内容
            - 执行测试实例的TearDown
        * 测试实例销毁(destruct)
    + 执行测试用例的TearDownTestCase
- 遍历执行Environment对象的TearDown

## 总结
1.Environment对象在所有测试用例执行前创建，并执行各自的SetUp方法；所有测试用例执行完成后，执行TearDown方法。
2.TestCase(测试用例)会为它名下的所有Tests唯一调用一次SetUpTestCase和TearDownTestCase方法。此时测试对象并未构建。
3.每一个测试实例的执行，均会单独构建实例，并调用一次SetUp和TearDown方法，所以测试实例间SetUp/TearDown中的内容，以及testing::Test对象中的非静态成员均是每次重新构建，非共享。而静态的成员会在同一测试用例下的所有测试实例间共享。