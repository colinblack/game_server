package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class ConcernReq
	{
		public static const PROTO:String = "ProtoFriend.ConcernReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public function ConcernReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ConcernReq
		{
			othuid = undefined;
			this.othuid = msgObj.othuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ConcernReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}