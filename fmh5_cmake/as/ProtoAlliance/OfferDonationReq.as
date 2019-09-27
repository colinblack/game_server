package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class OfferDonationReq
	{
		public static const PROTO:String = "ProtoAlliance.OfferDonationReq";
		public var package_root:*;
		public  var message:*;
		public var applyUid:int;
		public var propsid:int;
		public function OfferDonationReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			applyUid = undefined;
			propsid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.applyUid = this.applyUid;
			serializeObj.propsid = this.propsid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):OfferDonationReq
		{
			applyUid = undefined;
			propsid = undefined;
			this.applyUid = msgObj.applyUid;
			this.propsid = msgObj.propsid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OfferDonationReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}