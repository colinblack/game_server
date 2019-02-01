package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class UpGradeHeroStarReq
	{
		public static const PROTO:String = "ProtoHero.UpGradeHeroStarReq";
		public var package_root:*;
		public  var message:*;
		public var heroid:int;
		public var starid:int;
		public function UpGradeHeroStarReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			heroid = undefined;
			starid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.heroid = this.heroid;
			serializeObj.starid = this.starid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):UpGradeHeroStarReq
		{
			heroid = undefined;
			starid = undefined;
			this.heroid = msgObj.heroid;
			this.starid = msgObj.starid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UpGradeHeroStarReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}