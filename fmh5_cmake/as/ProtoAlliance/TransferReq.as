package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class TransferReq
	{
		public static const PROTO:String = "ProtoAlliance.TransferReq";
		public var package_root:*;
		public  var message:*;
		public var memberUid:int;
		public var otherName:Byte;
		public function TransferReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			memberUid = undefined;
			otherName = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.memberUid = this.memberUid;
			this.otherName.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):TransferReq
		{
			memberUid = undefined;
			otherName = undefined;
			this.memberUid = msgObj.memberUid;
			this.otherName = new Byte();
			this.otherName.writeArrayBuffer(msgObj.otherName);
			this.otherName.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):TransferReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}