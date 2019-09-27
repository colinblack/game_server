package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class UnlockPetResidenceResp
	{
		public static const PROTO:String = "ProtoPet.UnlockPetResidenceResp";
		public var package_root:*;
		public  var message:*;
		public var common:CommonItemsCPP;
		public function UnlockPetResidenceResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.common = this.common.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):UnlockPetResidenceResp
		{
			common = undefined;
			this.common = new CommonItemsCPP(package_root).unserialize(msgObj.common);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UnlockPetResidenceResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}