package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class CSCancelConcernReq
	{
		public static const PROTO:String = "ProtoFriend.CSCancelConcernReq";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var othuid:int;
		public function CSCancelConcernReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			othuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.othuid = this.othuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSCancelConcernReq
		{
			myuid = undefined;
			othuid = undefined;
			this.myuid = msgObj.myuid;
			this.othuid = msgObj.othuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSCancelConcernReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}