package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class FetchDonationResp
	{
		public static const PROTO:String = "ProtoAlliance.FetchDonationResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var donation:AllianceDonationCPP;
		public function FetchDonationResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			donation = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			if(this.donation!= undefined)
			{
				serializeObj.donation = this.donation.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):FetchDonationResp
		{
			commons = undefined;
			donation = undefined;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			if(msgObj.hasOwnProperty("donation"))
			{
				this.donation = new AllianceDonationCPP(package_root).unserialize(msgObj.donation);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FetchDonationResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}