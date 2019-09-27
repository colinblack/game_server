package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class ApproveJoinReq
	{
		public static const PROTO:String = "ProtoAlliance.ApproveJoinReq";
		public var package_root:*;
		public  var message:*;
		public var applyUid:int;
		public var operate:int;
		public function ApproveJoinReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			applyUid = undefined;
			operate = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.applyUid = this.applyUid;
			serializeObj.operate = this.operate;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ApproveJoinReq
		{
			applyUid = undefined;
			operate = undefined;
			this.applyUid = msgObj.applyUid;
			this.operate = msgObj.operate;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ApproveJoinReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}