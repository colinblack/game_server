package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class SeekDonationReq
	{
		public static const PROTO:String = "ProtoAlliance.SeekDonationReq";
		public var package_root:*;
		public  var message:*;
		public var propsid:int;
		public var count:int;
		public function SeekDonationReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			propsid = undefined;
			count = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.propsid = this.propsid;
			serializeObj.count = this.count;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SeekDonationReq
		{
			propsid = undefined;
			count = undefined;
			this.propsid = msgObj.propsid;
			this.count = msgObj.count;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SeekDonationReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}