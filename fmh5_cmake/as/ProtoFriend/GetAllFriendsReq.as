package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class GetAllFriendsReq
	{
		public static const PROTO:String = "ProtoFriend.GetAllFriendsReq";
		public var package_root:*;
		public  var message:*;
		public function GetAllFriendsReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetAllFriendsReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetAllFriendsReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}