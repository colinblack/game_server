package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class StripFansPushReq
	{
		public static const PROTO:String = "ProtoFriend.StripFansPushReq";
		public var package_root:*;
		public  var message:*;
		public var deluid:int;
		public function StripFansPushReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			deluid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.deluid = this.deluid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):StripFansPushReq
		{
			deluid = undefined;
			this.deluid = msgObj.deluid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):StripFansPushReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}