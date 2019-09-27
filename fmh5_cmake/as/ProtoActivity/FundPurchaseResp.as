package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class FundPurchaseResp
	{
		public static const PROTO:String = "ProtoActivity.FundPurchaseResp";
		public var package_root:*;
		public  var message:*;
		public var fundActivity:GameAcitivityCPP;
		public var commons:CommonItemsCPP;
		public function FundPurchaseResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			fundActivity = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.fundActivity = this.fundActivity.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):FundPurchaseResp
		{
			fundActivity = undefined;
			commons = undefined;
			this.fundActivity = new GameAcitivityCPP(package_root).unserialize(msgObj.fundActivity);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FundPurchaseResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}