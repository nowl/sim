#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <string>

class IPayload {};

template <class T>
class TypedPayload : public IPayload
{
private:
	T _val;

public:
	TypedPayload(const T& value) : _val(value) {}
	
	void set(const T& value) { _val = value; }
	
    const T& value() const { return _val; }
};

class Message
{
private:
	int sender, receiver, type;
	IPayload *payload;
	Message() {}

public:
	template <class T>
	static Message* make(int sender, int receiver, int type, const T& payload)
	{
		Message *message = new Message();
		message->sender = sender;
		message->receiver = receiver;
		message->type = type;
		message->set_payload(payload);
		return message;
	}
	
	~Message() { if (payload) delete payload; }
	
	template <class T>
	const T& get_payload() {
		return static_cast< TypedPayload<T>* >(payload)->value();
	}

	template <class T>
	void set_payload(T& value) {
		payload = new TypedPayload<T>(value);
	}
};

#endif /* __MESSAGE_HPP__ */
