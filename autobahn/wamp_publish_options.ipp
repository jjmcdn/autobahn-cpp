///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) Crossbar.io Technologies GmbH and contributors
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#include <msgpack.hpp>
#include <string>
#include <unordered_map>

namespace autobahn {

inline wamp_publish_options::wamp_publish_options()
    : m_exclude_me(true) //default
{
}

inline const bool& wamp_publish_options::exclude_me() const
{
    return m_exclude_me;
}

inline void wamp_publish_options::set_exclude_me(const bool& exclude_me)
{
    m_exclude_me = exclude_me;
}

} // namespace autobahn

namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
namespace adaptor {

template<>
struct convert<autobahn::wamp_publish_options>
{
    msgpack::object const& operator()(
            msgpack::object const& object,
            autobahn::wamp_publish_options& options) const
    {
        std::unordered_map<std::string, msgpack::object> options_map;
        object >> options_map;

        const auto options_map_itr = options_map.find("exclude_me");
        if (options_map_itr != options_map.end()) {
            options.set_exclude_me( options_map_itr->second.as<bool>());
        }

        return object;
    }
};

template<>
struct pack<autobahn::wamp_publish_options>
{
    template <typename Stream>
    msgpack::packer<Stream>& operator()(
            msgpack::packer<Stream>& packer,
            autobahn::wamp_publish_options const& options) const
    {
        std::unordered_map<std::string, unsigned> options_map;
        const auto& exclude_me = options.exclude_me();
        if (exclude_me != true) { //true is default, only false msut be transfered
            options_map["exclude_me"] = exclude_me;
        }

        packer.pack(options_map);

        return packer;
    }
};

template <>
struct object_with_zone<autobahn::wamp_publish_options>
{
    void operator()(
            msgpack::object::with_zone& object,
            const autobahn::wamp_publish_options& options)
    {
        std::unordered_map<std::string, msgpack::object> options_map;

        const auto& exclude_me = options.exclude_me();
        if (exclude_me != true) { //true is default, only false must be transfered
            options_map["exclude_me"] = msgpack::object(exclude_me);
        }

        object << options_map;
    }
};

} // namespace adaptor
} // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack
