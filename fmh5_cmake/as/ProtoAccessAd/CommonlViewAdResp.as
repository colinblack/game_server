package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class CommonlViewAdResp
	{
		public static const PROTO:String = "ProtoAccessAd.CommonlViewAdResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var ballon:BallonCPP;
		public function CommonlViewAdResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			ballon = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			if(this.ballon!= undefined)
			{
				serializeObj.ballon = this.ballon.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CommonlViewAdResp
		{
			commons = undefined;
			ballon = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			if(msgObj.hasOwnProperty("ballon"))
			{
				this.ballon = new BallonCPP(package_root).unserialize(msgObj.ballon);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CommonlViewAdResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}