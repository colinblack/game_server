package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class Base
	{
		public static const PROTO:String = "ProtoNPCUser.Base";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var registerPlatform:int;
		public var registerTime:int;
		public var lastLoginPlatform:int;
		public var lastLoginTime:int;
		public var loginTimes:int;
		public var loginDays:int;
		public var lastActiveTime:int;
		public var lastOffTime:int;
		public var forbidTs:int;
		public var forbidReason:Byte;
		public var tutorialStage:int;
		public var name:Byte;
		public var fig:Byte;
		public var exp:Number;
		public var level:int;
		public var acccharge:int;
		public var viplevel:int;
		public var cash:int;
		public var coin:int;
		public var firstRecharge:int;
		public var allianceId:int;
		public var barrier:Byte;
		public var lastcreateadts:int;
		public var allianAllowTs:int;
		public var nextDonationTs:int;
		public var helptimes:int;
		public var viprewarddailygiftts:int;
		public var vipdailyspeedproductcnt:int;
		public var vipdailyremoveordercdcnt:int;
		public var switchStatus:int;
		public function Base(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			registerPlatform = undefined;
			registerTime = undefined;
			lastLoginPlatform = undefined;
			lastLoginTime = undefined;
			loginTimes = undefined;
			loginDays = undefined;
			lastActiveTime = undefined;
			lastOffTime = undefined;
			forbidTs = undefined;
			forbidReason = undefined;
			tutorialStage = undefined;
			name = undefined;
			fig = undefined;
			exp = undefined;
			level = undefined;
			acccharge = undefined;
			viplevel = undefined;
			cash = undefined;
			coin = undefined;
			firstRecharge = undefined;
			allianceId = undefined;
			barrier = undefined;
			lastcreateadts = undefined;
			allianAllowTs = undefined;
			nextDonationTs = undefined;
			helptimes = undefined;
			viprewarddailygiftts = undefined;
			vipdailyspeedproductcnt = undefined;
			vipdailyremoveordercdcnt = undefined;
			switchStatus = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.registerPlatform = this.registerPlatform;
			serializeObj.registerTime = this.registerTime;
			serializeObj.lastLoginPlatform = this.lastLoginPlatform;
			serializeObj.lastLoginTime = this.lastLoginTime;
			serializeObj.loginTimes = this.loginTimes;
			serializeObj.loginDays = this.loginDays;
			serializeObj.lastActiveTime = this.lastActiveTime;
			serializeObj.lastOffTime = this.lastOffTime;
			serializeObj.forbidTs = this.forbidTs;
			this.forbidReason.pos = 0;
			serializeObj.tutorialStage = this.tutorialStage;
			this.name.pos = 0;
			this.fig.pos = 0;
			serializeObj.exp = this.exp;
			serializeObj.level = this.level;
			serializeObj.acccharge = this.acccharge;
			serializeObj.viplevel = this.viplevel;
			serializeObj.cash = this.cash;
			serializeObj.coin = this.coin;
			serializeObj.firstRecharge = this.firstRecharge;
			serializeObj.allianceId = this.allianceId;
			this.barrier.pos = 0;
			serializeObj.lastcreateadts = this.lastcreateadts;
			serializeObj.allianAllowTs = this.allianAllowTs;
			serializeObj.nextDonationTs = this.nextDonationTs;
			serializeObj.helptimes = this.helptimes;
			serializeObj.viprewarddailygiftts = this.viprewarddailygiftts;
			serializeObj.vipdailyspeedproductcnt = this.vipdailyspeedproductcnt;
			serializeObj.vipdailyremoveordercdcnt = this.vipdailyremoveordercdcnt;
			serializeObj.switchStatus = this.switchStatus;
			return serializeObj;
		}
		public function unserialize(msgObj:*):Base
		{
			uid = undefined;
			registerPlatform = undefined;
			registerTime = undefined;
			lastLoginPlatform = undefined;
			lastLoginTime = undefined;
			loginTimes = undefined;
			loginDays = undefined;
			lastActiveTime = undefined;
			lastOffTime = undefined;
			forbidTs = undefined;
			forbidReason = undefined;
			tutorialStage = undefined;
			name = undefined;
			fig = undefined;
			exp = undefined;
			level = undefined;
			acccharge = undefined;
			viplevel = undefined;
			cash = undefined;
			coin = undefined;
			firstRecharge = undefined;
			allianceId = undefined;
			barrier = undefined;
			lastcreateadts = undefined;
			allianAllowTs = undefined;
			nextDonationTs = undefined;
			helptimes = undefined;
			viprewarddailygiftts = undefined;
			vipdailyspeedproductcnt = undefined;
			vipdailyremoveordercdcnt = undefined;
			switchStatus = undefined;
			this.uid = msgObj.uid;
			this.registerPlatform = msgObj.registerPlatform;
			this.registerTime = msgObj.registerTime;
			this.lastLoginPlatform = msgObj.lastLoginPlatform;
			this.lastLoginTime = msgObj.lastLoginTime;
			this.loginTimes = msgObj.loginTimes;
			this.loginDays = msgObj.loginDays;
			this.lastActiveTime = msgObj.lastActiveTime;
			this.lastOffTime = msgObj.lastOffTime;
			this.forbidTs = msgObj.forbidTs;
			this.forbidReason = new Byte();
			this.forbidReason.writeArrayBuffer(msgObj.forbidReason);
			this.forbidReason.pos = 0;
			this.tutorialStage = msgObj.tutorialStage;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.fig = new Byte();
			this.fig.writeArrayBuffer(msgObj.fig);
			this.fig.pos = 0;
			this.exp = msgObj.exp;
			this.level = msgObj.level;
			this.acccharge = msgObj.acccharge;
			this.viplevel = msgObj.viplevel;
			this.cash = msgObj.cash;
			this.coin = msgObj.coin;
			this.firstRecharge = msgObj.firstRecharge;
			this.allianceId = msgObj.allianceId;
			this.barrier = new Byte();
			this.barrier.writeArrayBuffer(msgObj.barrier);
			this.barrier.pos = 0;
			this.lastcreateadts = msgObj.lastcreateadts;
			this.allianAllowTs = msgObj.allianAllowTs;
			this.nextDonationTs = msgObj.nextDonationTs;
			this.helptimes = msgObj.helptimes;
			this.viprewarddailygiftts = msgObj.viprewarddailygiftts;
			this.vipdailyspeedproductcnt = msgObj.vipdailyspeedproductcnt;
			this.vipdailyremoveordercdcnt = msgObj.vipdailyremoveordercdcnt;
			this.switchStatus = msgObj.switchStatus;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):Base
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}