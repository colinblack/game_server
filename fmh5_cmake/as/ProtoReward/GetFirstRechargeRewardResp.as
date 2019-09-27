package com.sanguo.game.server.connectlogic.common.message.ProtoReward
{
	import laya.utils.Byte;
	public class GetFirstRechargeRewardResp
	{
		public static const PROTO:String = "ProtoReward.GetFirstRechargeRewardResp";
		public var package_root:*;
		public  var message:*;
		public var firstRecharge:int;
		public var common:CommonItemsCPP;
		public var theme:ThemeInfoResp;
		public function GetFirstRechargeRewardResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			firstRecharge = undefined;
			common = undefined;
			theme = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.firstRecharge = this.firstRecharge;
			serializeObj.common = this.common.serialize();
			if(this.theme!= undefined)
			{
				serializeObj.theme = this.theme.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFirstRechargeRewardResp
		{
			firstRecharge = undefined;
			common = undefined;
			theme = undefined;
			this.firstRecharge = msgObj.firstRecharge;
			this.common = new CommonItemsCPP(package_root).unserialize(msgObj.common);
			if(msgObj.hasOwnProperty("theme"))
			{
				this.theme = new ThemeInfoResp(package_root).unserialize(msgObj.theme);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFirstRechargeRewardResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}