package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class CancelConcernReq
	{
		public static const PROTO:String = "ProtoFriend.CancelConcernReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public function CancelConcernReq(root:*)
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
		public function unserialize(msgObj:*):CancelConcernReq
		{
			othuid = undefined;
			this.othuid = msgObj.othuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CancelConcernReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}