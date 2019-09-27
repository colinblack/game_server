package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class GetFriendHelpInfoReq
	{
		public static const PROTO:String = "ProtoFriend.GetFriendHelpInfoReq";
		public var package_root:*;
		public  var message:*;
		public function GetFriendHelpInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFriendHelpInfoReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFriendHelpInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}