package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class UpGradeHeroSkillReq
	{
		public static const PROTO:String = "ProtoHero.UpGradeHeroSkillReq";
		public var package_root:*;
		public  var message:*;
		public var heroid:int;
		public var skillid:int;
		public function UpGradeHeroSkillReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			heroid = undefined;
			skillid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.heroid = this.heroid;
			serializeObj.skillid = this.skillid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):UpGradeHeroSkillReq
		{
			heroid = undefined;
			skillid = undefined;
			this.heroid = msgObj.heroid;
			this.skillid = msgObj.skillid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UpGradeHeroSkillReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}