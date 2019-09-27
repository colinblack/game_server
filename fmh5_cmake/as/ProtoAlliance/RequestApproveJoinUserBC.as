package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestApproveJoinUserBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestApproveJoinUserBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var applyUid:int;
		public var operate:int;
		public function RequestApproveJoinUserBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			applyUid = undefined;
			operate = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.applyUid = this.applyUid;
			serializeObj.operate = this.operate;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestApproveJoinUserBC
		{
			aid = undefined;
			uid = undefined;
			applyUid = undefined;
			operate = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.applyUid = msgObj.applyUid;
			this.operate = msgObj.operate;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestApproveJoinUserBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}