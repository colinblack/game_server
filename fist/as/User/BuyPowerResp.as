package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class BuyPowerResp
	{
		public static const PROTO:String = "User.BuyPowerResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function BuyPowerResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyPowerResp
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyPowerResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}