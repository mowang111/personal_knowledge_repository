## 1. 单例模式是什么？
一个类只允许创建一个对象（或者叫实例），那这个类就是单例类。这个设计模式就是单例设计模式，简称单例模式。

## 2. 单例模式有什么用？
有些数据在系统中只应该保存一份，就比较适合设计为单例类，比如系统的配置信息。
另外，可以使用单例解决资源访问冲突的问题。
考虑以下场景：
你设计了一个日志类：
```c++
#include <fstream>
class Logger {
private:
	std::ofstream writer;

public:
	Logger() {
		writer.open("./log.txt", std::ios::app) //std::ios::app for append
		if(!writer){
			//Handle file open error
		}
	}

	void log(const std::string& message){
		writer << message;
	}

	~Logger() {
		if(writer.is_open()) {
			writer.close();
		}
	}
	
};

class UserController {
private:
	Logger logger;

public:
	void login(const std::string& username, const std::string& password) {
		logger.log(username + " logined!");
	}
}

class Order() {
private:
	Logger logger;

public:
	void create(){
		logger.log("order created!");
	}
}
```

上述代码实现了简单的日志单例类，但是当多线程的情况下，多个线程同时操作不同的日志类写入，会造成日志混乱。

这时候考虑：
+ 当日志设计为单例类的时候，同时需要将写入这个操作加一个对象锁。
+ 如果不设计单例类，需要将写入操作加一个类锁。

## 3. 如何实现单例模式？

### 3.1 饿汉模式
饿汉模式在类加载的适合，instance静态实例就以及创建完成并初始化好了，所以instance实例的创建过程是线程安全的，但是这种实现方式不支持延迟加载。
```c++
class Logger {
private:
	std::ofstream writer;
	static Logger instance;
	Logger() {
		writer.open("./log.txt", std::ios::app) //std::ios::app for append
		if(!writer){
			//Handle file open error
		}
	}
	~Logger() {
		if(writer.is_open()) {
			writer.close();
		}
	}
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
public:
	static Logger& GetInstance() {
		return instance;
	}
}
Logger Logger::instance;
```
不支持延时加载，如果实例占用资源多或者初始化耗时长，会浪费资源（但是也避免了在使用过程中影响系统性能，也能及时暴露问题）。

### 3.2 懒汉模式
```c++
#include <iostream>
#include <fstream>
#include <mutex>
class Logger {
private:
	std::ofstream writer;
	static Logger* instance;
	static std::mutex mtx;
	Logger() {
		writer.open("./log.txt", std::ios::app) //std::ios::app for append
		if(!writer){
			//Handle file open error
		}
	}
	~Logger() {
		if(writer.is_open()) {
			writer.close();
		}
	}
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
public:
	static Logger& GetInstance() {
		std::lock_guard<std::mutex> lock(mtx);
		if (instance == nullptr) {
			instance = new Logger();
		}
		return instance;
	}
};
```

### 3.3 双重检测

```c++
#include <iostream>
#include <fstream>
#include <mutex>
class Logger {
private:
	std::ofstream writer;
	static Logger* instance;
	static std::mutex mtx;
	Logger() {
		writer.open("./log.txt", std::ios::app) //std::ios::app for append
		if(!writer){
			//Handle file open error
		}
	}
	~Logger() {
		if(writer.is_open()) {
			writer.close();
		}
	}
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
public:
	static Logger& GetInstance() {
		if (instance == nullptr) {
			std::lock_guard<std::mutex> lock(mtx);
			if (instance == nullptr) {
				instance = new Logger();
			}
		}
		return instance;
	}
};
```

### 3.4 Meyer's Singleton
```c++
#include <iostream>
#include <fstream>
#include <mutex>

class Logger {
private:
    std::ofstream writer;

    Logger() {
        writer.open("./log.txt", std::ios::app); // Fixed missing semicolon here
        if(!writer) {
            // Handle file open error
        }
    }

    ~Logger() {
        if(writer.is_open()) {
            writer.close();
        }
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& GetInstance() {
        static Logger instance;  // This is the Meyer's Singleton approach
        return instance;
    }
};

int main() {
    Logger& logger = Logger::GetInstance();
    // Use the logger instance as needed
    return 0;
}

```
Meyer's Singleton 是一种在 C++ 中实现单例模式的方法，由 Scott Meyers 提出。它的主要特点是使用静态局部变量来实现单例对象的延迟初始化。

Meyer's Singleton 的主要优势是其简洁性和在 C++11 及其后续版本中的线程安全性。在 C++11 中，局部静态变量的初始化被保证是线程安全的，这意味着在并发环境中不需要额外的锁机制来确保单例对象只被创建一次。