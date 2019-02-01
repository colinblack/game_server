package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetFriendsReq
	{
		public static const PROTO:String = "ProtoFriend.ProtoGetFriendsReq";
		public var package_root:*;
		public  var message:*;
		public function ProtoGetFriendsReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetFriendsReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetFriendsReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}