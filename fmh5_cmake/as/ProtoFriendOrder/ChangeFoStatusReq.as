package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class ChangeFoStatusReq
	{
		public static const PROTO:String = "ProtoFriendOrder.ChangeFoStatusReq";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var myindex:int;
		public var newstatus:int;
		public function ChangeFoStatusReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			myindex = undefined;
			newstatus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.myindex = this.myindex;
			serializeObj.newstatus = this.newstatus;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ChangeFoStatusReq
		{
			myuid = undefined;
			myindex = undefined;
			newstatus = undefined;
			this.myuid = msgObj.myuid;
			this.myindex = msgObj.myindex;
			this.newstatus = msgObj.newstatus;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ChangeFoStatusReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}