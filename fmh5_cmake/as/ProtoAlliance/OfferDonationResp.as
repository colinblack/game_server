package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class OfferDonationResp
	{
		public static const PROTO:String = "ProtoAlliance.OfferDonationResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var donation:AllianceDonationCPP;
		public function OfferDonationResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			donation = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.donation = this.donation.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):OfferDonationResp
		{
			commons = undefined;
			donation = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.donation = new AllianceDonationCPP(package_root).unserialize(msgObj.donation);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OfferDonationResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}