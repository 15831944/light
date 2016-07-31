#pragma once

#include <memory>

#include "channel.h"
#include "async_worker.h"

class client_peer;

class channel_manager
{
public:
    channel_manager();
    ~channel_manager();

    void start();

    void on_update();

public: // packet events
    bool enter(client_peer* peer, channel::index index, light::FlatBuffersPtr<PACKET::ENTER> packet);

    bool leave(client_peer* peer, channel::index index, light::FlatBuffersPtr<PACKET::LEAVE> packet);

    void broadcast(client_peer* peer, channel::index index, light::FlatBuffersPtr<PACKET::BROADCAST> packet);

public:
    void on_redis_event(const std::string& msg);

public:

    template <typename T>
    inline void	strand_post_job(T handler, int position)
    {
        m_async_worker->strand_post_job(handler, position);
    }

public:
    int channel_manager_strand_position() const // 0���� ä�θŴ����� �ܺ� �̺�Ʈ���� strand ������.
    {
        return 0;
    }

    int channel_strand_position(int channel_no) const
    {
        return (channel_no % std::max<int>(m_channels.size() - 1, 1)) + 1; // 1~�ִ� ä�ΰ����� �̾Ƽ� ���ٽ�Ű���Ϸ� �ϴ� �ǵ�.
    }

private:
    std::unique_ptr<light::async_worker> m_async_worker;

    std::unordered_map<channel::index, std::shared_ptr<channel> > m_channels;
};
