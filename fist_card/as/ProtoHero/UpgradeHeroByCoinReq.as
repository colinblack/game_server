package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class UpgradeHeroByCoinReq
	{
		public static const PROTO:String = "ProtoHero.UpgradeHeroByCoinReq";
		public var package_root:*;
		public  var message:*;
		public var heroid:int;
		public var oneclick:int;
		public function UpgradeHeroByCoinReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			heroid = undefined;
			oneclick = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.heroid = this.heroid;
			serializeObj.oneclick = this.oneclick;
			return serializeObj;
		}
		public function unserialize(msgObj:*):UpgradeHeroByCoinReq
		{
			heroid = undefined;
			oneclick = undefined;
			this.heroid = msgObj.heroid;
			this.oneclick = msgObj.oneclick;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UpgradeHeroByCoinReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}