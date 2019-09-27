package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class SeekDonationResp
	{
		public static const PROTO:String = "ProtoAlliance.SeekDonationResp";
		public var package_root:*;
		public  var message:*;
		public var donation:AllianceDonationCPP;
		public var nextDonationTs:int;
		public function SeekDonationResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			donation = undefined;
			nextDonationTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.donation = this.donation.serialize();
			serializeObj.nextDonationTs = this.nextDonationTs;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SeekDonationResp
		{
			donation = undefined;
			nextDonationTs = undefined;
			this.donation = new AllianceDonationCPP(package_root).unserialize(msgObj.donation);
			this.nextDonationTs = msgObj.nextDonationTs;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SeekDonationResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}